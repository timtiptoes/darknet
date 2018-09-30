
#include <Arduino.h>
#include <SoftwareSerial.h>
#include "WiFly.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Servo.h> 
Servo myservo;  // create servo object to control a servo 
// 1) Enter in your SSID and KEY
// 2) Once you've uploaded this to the Arduino, open the serial monitor and wait until
//       it says 'Web server ready'
// 3) Go to a web browser on your network and use the IP you got from the serial monitor
//       and enter an x and y in the get parameters.
//       This is for my network: 
//               http://192.168.1.125/?x=45&y=45
// For now only the x channel works, so the y value is meaningless

#define SSID      "<YOUR SSID>"
#define KEY       "<Your network key>"
#define SSID      "ATTxUERtUI"
#define KEY       "dontfear7thegipper8"

#define AUTH      WIFLY_AUTH_WPA2_PSK

char type[8]; // GET or POST
char path[100]; // /info etc.
char protocol[128]; // HTTP/1.1
char dummy1[20],dummy2[20];
char first_line[400];
char cc;
int i,x,y,xl,yl;
char ip[16];

// Pins' connection
// Arduino       WiFly
//  2    <---->    TX
//  3    <---->    RX
SoftwareSerial uart(2, 3);
WiFly wifly(&uart);

void setup() {
  myservo.write(0);

  myservo.attach(9);  //the pin for the servo control 
  myservo.attach(10);  //the pin for the servo control 

  delay(200);
  myservo.detach();
  
  uart.begin(9600);

  Serial.begin(9600);
  Serial.println("--------- Web Servo Control --------");

  // wait for initilization of wifly
  delay(3000);

  uart.begin(9600);     // WiFly UART Baud Rate: 9600

  wifly.reset();
  delay(1000);


  wifly.sendCommand("set ip local 80\r"); // set the local comm port to 80
  delay(100);

  wifly.sendCommand("set comm remote 0\r"); // do not send a default string when a connection opens
  delay(100);

  wifly.sendCommand("set comm open *OPEN*\r"); // set the string that the wifi shield will output when a connection is opened
  delay(100);

  Serial.println("Join " SSID );
  if (wifly.join(SSID, KEY, AUTH)) {
    Serial.println("OK");
  } 
  else {
    Serial.println("Failed");
  }
  delay(5000);

  wifly.sendCommand("get ip\r");
  uart.setTimeout(500);
  if(!uart.find("IP="))
  {
    Serial.println("can not get ip");
    while(1);
    ;
  }
  else
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
  while (wifly.receive((uint8_t *)&c, 1, 300) > 0);
  ;
  
  Serial.println("Web server ready");
    wifly.sendCommand("set comm idle 4");
  
}

void loop() {
  if (wifly.available()) {
    if(uart.find("*OPEN*")) // see if the data available is from an open connection by looking for the *OPEN* string
    {
      Serial.println("New Browser Request!");
      delay(1000); // delay enough time for the browser to complete sending its HTTP request string

      i=0;
      cc=uart.read();
      while (cc!='\n'){
        first_line[i]=cc;
        i++;
        cc=uart.read();
      }
      first_line[i] = '\0'; 
      Serial.print("Just read:\n\t");
      Serial.println(first_line);

      sscanf(first_line, "GET %s", path);
      Serial.println("Just read:");
      Serial.println(path);

      sscanf(path,"%4s%d%3s%d",dummy1,&x,dummy2,&y);
      Serial.println(x);
      Serial.println(y);
      Serial.println("And the last ones are");
      Serial.println(xl);
      Serial.println(yl);
      if ((x!=xl) || (y!=yl)){
        Serial.println("Received different coordinates\n");
        Serial.println(x);
        Serial.println(y);
        myservo. attach(9);
        delay(200);
        myservo.write(x); //convert readString to number for servo
        delay(200);
        //myservo.detach();

        myservo.attach(10);
        delay(200);
        myservo.write(y); //convert readString to number for servo
        delay(200);
        myservo.detach();
      }
      xl=x;
      yl=y;
      
      wifly.println("HTTP/1.1 200 OK");
      wifly.println("Content-Type: text/html; charset=UTF-8");
      wifly.println("Content-Length: 59"); // length of HTML code
      wifly.println("Connection: close");
      wifly.println();

      wifly.print("<html><head></head><body>coordinates received</body></html>");
    }
  }
}


