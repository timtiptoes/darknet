#include <Arduino.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Servo.h> 
#include <SoftwareSerial.h>
#include "WiFly.h"

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
int i,x,y,xl,yl,xs,ys;
char ip[16];

// Pins' connection
// Arduino       WiFly
//  2    <---->    TX
//  3    <---->    RX
SoftwareSerial uart(2, 3);
WiFly wifly(&uart);

/* How should setup work
Get upper left
Get lower right

Get anything
  While button not pressed
    get pot readings
    if x changed more by delta
      then move x there
    if y changed more than delta
      the move y there
  Return pot readings
    



*/


Servo myxservo; 
Servo myyservo;

int x0=0,y0=0,x1=0,y1=0;

   
int xPin = 0;
int yPin = 1;
                  
int ledPin1 = 13;
  
int ledPin2 = 14;

const int button1Pin = 2;  // pushbutton 1 pin

int button1State;

struct pair {
    int x;
    int y;
};

void init_wifli(){
    uart.begin(9600);

  Serial.begin(9600);
  Serial.println("--------- Web Servo Control --------");

  // wait for initialization of wifly
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

struct pair get_pot_reading()
{
  int xValue,yValue,xs_old=0,xs,ys,ys_old=0;
  button1State = digitalRead(button1Pin);
  xValue = analogRead(xPin);  
  yValue = analogRead(yPin);

  
  while(button1State == HIGH){
    xValue = analogRead(xPin);  
    yValue = analogRead(yPin);

    button1State = digitalRead(button1Pin);
    xs=map(xValue,0,1023,0,180);
    if ((abs(xs-xs_old)>5)){
      myxservo.write(xs);
      xs_old=xs;
    }
    ys=map(yValue,0,1023,0,180);
    if ((abs(ys-ys_old)>5)){
      myyservo.write(ys);
      ys_old=ys;
    }
  }
  pair r = {xs_old,ys_old};
  Serial.println("Just sent these corners:");
Serial.print(xs);
Serial.print(",");
Serial.println(ys);
return r;
}

void setup() // this function runs once when the sketch starts up
{
  // Initialize serial communication at 115200 baud
  Serial.begin(9600);
   while (!Serial) {
    ; // wait for serial port to connect.
  }
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(button1Pin, INPUT);
  myxservo.write(0); //set initial servo position to 0
  myxservo.attach(9);

  myyservo.write(0);
  myyservo.attach(10);

    // Get bounding box

  digitalWrite(ledPin1, HIGH);     // Turn the LED on
  Serial.println("Waiting for lower_right...");

  struct pair lower_right = get_pot_reading();
  int x0=lower_right.x;
  int y0=lower_right.y;
  Serial.println("Just read lower right");
  Serial.print(x0);
  Serial.print(",");
  Serial.println(y0);
  digitalWrite(ledPin1, LOW);      // Turn the LED offr right corner
  delay(1000);
  digitalWrite(ledPin1, HIGH);     // Turn the LED on
  struct pair upper_left = get_pot_reading();
  int x1=upper_left.x;
  int y1=upper_left.y;
  digitalWrite(ledPin1, LOW);      // Turn the LED offr right corner
  Serial.println("Just read these corners:");
  Serial.print(x0);
  Serial.print(",");
  Serial.println(y0);

  Serial.print(x1);
  Serial.print(",");
  Serial.println(y1);

  Serial.println("Initializing WiFly...");
  init_wifli();

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
        xs=map(x,0,180,53,165);
        delay(200);
        myservo.write(xs); //convert readString to number for servo
        delay(200);
        //myservo.detach();
         
        myservo.attach(10);
        delay(200);
        ys=map(y,0,180,180,0);
        myservo.write(ys); //convert readString to number for servo
        Serial.println("Just wrote to scaled coordinates:");
        Serial.println(xs);
        Serial.println(ys);
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
