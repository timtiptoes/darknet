#include <Arduino.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Servo.h> 

Servo myservo; 

int x0=0,y0=0,x1=0,y1=0;

   
int xPin = 0;
int yPin = 1;
                  
int ledPin1 = 13;
  
int ledPin2 = 14;
int xs_old=0;

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
  
  while(LOW == HIGH){
    xValue = analogRead(xPin);  
    yValue = analogRead(yPin);
    button1State = digitalRead(button1Pin);
  }
  pair r = {xValue,yValue};
return r;
}

void setup() // this function runs once when the sketch starts up
{
  myservo.write(0);

  myservo.attach(9);  //the pin for the servo control 

  delay(200);
  myservo.detach();
  
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

Serial.print(x1);
Serial.print(",");
Serial.println(y1);


}


void loop() // this function runs repeatedly after setup() finishes
{
struct pair lower_right = get_pot_reading();
int x0=lower_right.x;
int y0=lower_right.y;
int xs=map(x0,0,1023,0,180);
if ((abs(xs-xs_old)>5)){
  myservo. attach(9);
  delay(200);
  myservo.write(xs); //convert readString to number for servo
  delay(200);
  myservo.detach();
}
//Serial.print(x0);
//Serial.print(",");
//Serial.println(y0);
Serial.println("mapping ");
Serial.print(x0);
Serial.print(" to ");
Serial.print(xs);
Serial.print(" and xs_old is ");
Serial.println(xs_old);
  delay(300);
xs_old=xs;

  
}
