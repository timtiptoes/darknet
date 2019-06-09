
#include <Arduino.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Servo.h> 
#include <SoftwareSerial.h>
#include "WiFly.h"
#include <Wire.h>


#define SSID      "ATTxUERtUI"
#define KEY       "dontfear7thegipper8"

#define AUTH      WIFLY_AUTH_WPA2_PSK
Servo myservo;
char type[8]; // GET or POST
char path[30]; // /info etc.
//char path[100]; // /info etc.
//char protocol[128]; // HTTP/1.1
char dummy1[20],dummy2[20];
char first_line[100];
//char first_line[400];
char cc;
int i,x,y,xl,yl,xs,ys;
char ip[16];

// Pins' connection
// Arduino       WiFly
//  2    <---->    TX
//  3    <---->    RX


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

SoftwareSerial uart(2, 3);
WiFly wifly(&uart);
  

int x0=0,y0=0,x1=0,y1=0;   
int xPin = 0;
int yPin = 1;            
int button1State;


#include <tims_utils.h>


void setup() // this function runs once when the sketch starts up
{
  // Initialize serial communication at 115200 baud
  init_serial(Serial);

    // Get bounding box

  digitalWrite(13, HIGH);     // Turn the LED on
  Serial.println("Waiting for lower_right...");

  struct pair lower_right = get_pot_reading(Serial);
  int x0=lower_right.x;
  int y0=lower_right.y;
  //digitalWrite(13, LOW);      // Turn the LED offr right corner
  //delay(1000);
  //digitalWrite(13, HIGH);     // Turn the LED on

  Serial.println("Waiting for upper_left...");
  struct pair upper_left = get_pot_reading(Serial);
  int x1=upper_left.x;
  int y1=upper_left.y;
  //digitalWrite(13, LOW);      // Turn the LED offr right corner
  delay(5000);

  
  Serial.println("Initializing Wire...");
  Wire.begin();
  delay(5000);
  Serial.println("Initializing WiFly...");
    init_wifli();

    delay(1000);

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
       xs=map(x,0,640,x1,x0);
       ys=map(y,0,480,y1,y0);

        char out_string[7]="";
        sprintf(out_string, "%03d,%03d", x,y);
        Serial.print("Transmitting:");
        Serial.println(out_string);
        transmit_coordinates(Wire,out_string);

        delay(2000);

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
}
