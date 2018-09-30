#include <Arduino.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
Tim!
  Check that pin14 is also a digital out
  Check that pin 1 is also an analog in
*/

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

struct pair get_pot_reading()
{
  int xValue,yValue;
  button1State = digitalRead(button1Pin);
  xValue = analogRead(xPin);  
  yValue = analogRead(yPin);
  
  while(button1State == HIGH){
    xValue = analogRead(xPin);  
    yValue = analogRead(yPin);
    button1State = digitalRead(button1Pin);
  }
  pair r = {xValue,yValue};
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


digitalWrite(ledPin1, HIGH);     // Turn the LED on
struct pair lower_right = get_pot_reading();
int x0=lower_right.x;
int y0=lower_right.y;
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


}


void loop() // this function runs repeatedly after setup() finishes
{

  delay(5);
  
}
