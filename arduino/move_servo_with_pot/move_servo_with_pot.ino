#include <Arduino.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Servo.h> 
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


}


void loop() // this function runs repeatedly after setup() finishes
{
  while (HIGH == HIGH) {
    delay(100);
  }
  
}
