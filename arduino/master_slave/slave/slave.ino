// Chapter 7 - Communications
// I2C Slave
// By Cornel Amariei for Packt Publishing

// Include the required Wire library for I2C
#include <Wire.h>
#include <stdio.h>
#include <string.h>
#include <Servo.h> 


int LED = 13;
char recd_string[7] ="";
char old_recd_string[7]="";
char c;
int i;

Servo myxservo; 
Servo myyservo;

#include <slave_utils.h>


void setup() {
    Serial.begin(9600); 
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
    Serial.print("Starting setup...");
  // Define the LED pin as Output
  pinMode (LED, OUTPUT);
  // Start the I2C Bus as Slave on address 9
  Wire.begin(9); 
  // Attach a function to trigger when something is received.
  Wire.onReceive(receiveEvent);

  myxservo.write(0); //set initial servo position to 0
  myxservo.attach(9);

  myyservo.write(0);
  myyservo.attach(10);


}



void loop() {
  if (strcmp(recd_string,old_recd_string)!=0){
    
    struct pair result=convert_string(recd_string);
    
    strcpy(old_recd_string,recd_string);
    Serial.print(result.x);
    Serial.print("----");
    Serial.println(result.y);
    move_servo(result);

  }
}
