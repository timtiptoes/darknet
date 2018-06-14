#include <SoftwareSerial.h>
#include "WiFly.h"

#define SSID      "ATTxUERtUI"
#define KEY       "dontfear7thegipper8"
// check your access point's security mode, mine was WPA20-PSK
// if yours is different you'll need to change the AUTH constant, see the file WiFly.h for avalable security codes
#define AUTH      WIFLY_AUTH_WPA2_PSK

int flag = 0;

// Pins' connection
// Arduino       WiFly
//  2    <---->    TX
//  3    <---->    RX

SoftwareSerial wiflyUart(2, 3); // create a WiFi shield serial object
WiFly wifly(&wiflyUart); // pass the wifi siheld serial object to the WiFly class
char ip[16];

void setup()
{
    pinMode(11,OUTPUT);
    digitalWrite(11,LOW);

    pinMode(12,OUTPUT);
    digitalWrite(12,LOW);

    pinMode(13,OUTPUT);
    digitalWrite(13,LOW);

    wiflyUart.begin(9600); // start wifi shield uart port

    Serial.begin(9600); // start the arduino serial port
    Serial.println("--------- WIFLY Webserver --------");

    // wait for initilization of wifly
    delay(1000);

    wifly.reset(); // reset the shield
    delay(1000);
    //set WiFly params

    wifly.sendCommand("set ip local 80\r"); // set the local comm port to 80
    delay(100);

    wifly.sendCommand("set comm remote 0\r"); // do not send a default string when a connection opens
    delay(100);

    wifly.sendCommand("set comm open *OPEN*\r"); // set the string that the wifi shield will output when a connection is opened
    delay(100);

    Serial.println("Join " SSID );
    if (wifly.join(SSID, KEY, AUTH)) {
        Serial.println("OK");
    } else {
        Serial.println("Failed");
    }

    delay(5000);

    wifly.sendCommand("get ip\r");

    wiflyUart.setTimeout(500);
    if(!wiflyUart.find("IP="))
    {
        Serial.println("can not get ip");
        while(1);;
    }else
    {
        Serial.print("IP:");
    }

    char c;
    int index = 0;
    while (wifly.receive((uint8_t *)&c, 1, 300) > 0) { // print the response from the get ip command
        if(c == ':')
        {
            ip[index] = 0;
            break;
        }
        ip[index++] = c;
        Serial.print((char)c);

    }
    Serial.println();
    while (wifly.receive((uint8_t *)&c, 1, 300) > 0);;
    Serial.println("Web server ready");
}

void loop()
{
    if(wifly.available())       // the wifi shield has data available
    {

        if(wiflyUart.find("*OPEN*")) // see if the data available is from an open connection by looking for the *OPEN* string
        {
            Serial.println("New Browser Request!");
            delay(1000); // delay enough time for the browser to complete sending its HTTP request string

            if(wiflyUart.find("pin=")) // look for the string "pin=" in the http request, if it's there then we want to control the LED
            {
                Serial.println("LED Control");
                // the user wants to toggle the LEDs
                int pinNumber = (wiflyUart.read()-48); // get first number i.e. if the pin 13 then the 1st number is 1
                int secondNumber = (wiflyUart.read()-48);
                if(secondNumber>=0 && secondNumber<=9)
                {
                    pinNumber*=10;
                    pinNumber +=secondNumber; // get second number, i.e. if the pin number is 13 then the 2nd number is 3, then add to the first number
                }
                digitalWrite(pinNumber, !digitalRead(pinNumber)); // toggle pin
                // Build pinstate string. The Arduino replies to the browser with this string.
                String pinState = "Pin ";
                pinState+=pinNumber;
                pinState+=" is ";
                if(digitalRead(pinNumber)) // check if the pin is ON or OFF
                {
                    pinState+="ON"; // the pin is on
                }
                else
                {
                    pinState+="OFF";  // the pin is off
                }
                // build HTTP header Content-Length string.
                String contentLength="Content-Length: ";
                contentLength+=pinState.length(); // the value of the length is the lenght of the string the Arduino is replying to the browser with.
                // send HTTP header
                wiflyUart.println("HTTP/1.1 200 OK");
                wiflyUart.println("Content-Type: text/html; charset=UTF-8");
                wiflyUart.println(contentLength); // length of HTML code
                wiflyUart.println("Connection: close");
                wiflyUart.println();
                // send response
                wiflyUart.print(pinState);
            }
            else
            {
                // send HTTP header
                wiflyUart.println("HTTP/1.1 200 OK");
                wiflyUart.println("Content-Type: text/html; charset=UTF-8");
                wiflyUart.println("Content-Length: 540"); // length of HTML code
                wiflyUart.println("Connection: close");
                wiflyUart.println();

                // send webpage's HTML code
                wiflyUart.print("<html>");
                wiflyUart.print("<head>");
                wiflyUart.print("<title>WiFi Shield Webpage</title>");
                wiflyUart.print("</head>");
                wiflyUart.print("<body>");
                wiflyUart.print("<h1>LED Toggle Webpage</h1>");
                // In the <button> tags, the ID attribute is the value sent to the arduino via the "pin" GET parameter
                wiflyUart.print("<button id=\"11\" class=\"led\">Toggle Pin 11</button> "); // button for pin 11
                wiflyUart.print("<button id=\"12\" class=\"led\">Toggle Pin 12</button> "); // button for pin 12
                wiflyUart.print("<button id=\"13\" class=\"led\">Toggle Pin 13</button> "); // button for pin 13
                wiflyUart.print("<script src=\"http://ajax.googleapis.com/ajax/libs/jquery/2.1.3/jquery.min.js\"></script>");
                wiflyUart.print("<script type=\"text/javascript\">");
                wiflyUart.print("$(document).ready(function(){");
                wiflyUart.print("$(\".led\").click(function(){");
                wiflyUart.print("var p = $(this).attr('id');"); // get id value (i.e. pin13, pin12, or pin11)
                // send HTTP GET request to the IP address with the parameter "pin" and value "p", then execute the function
                // IMPORTANT: dont' forget to replace the IP address and port with YOUR shield's IP address and port
                wiflyUart.print("$.get(\"http://");
                wiflyUart.print(ip);
                wiflyUart.print(":80/a\", {pin:p},function(data){alert(data)});");// execute get request. Upon return execute the "function" (display an alert with the "data" send back to the browser.
                wiflyUart.print("});");
                wiflyUart.print("});");
                wiflyUart.print("</script>");
                wiflyUart.print("</body>");
                wiflyUart.print("</html>");
            }
            Serial.println("Data sent to browser");
        }
    }
}
