

/* 
 With this script you can enter coordinates into the serial monitor to send a servo to that position;
 */

#include <Servo.h> 
String readString;

Servo myservo;

void setup() 
{ 
  Serial.begin(9600);
  myservo.write(0); //set initial servo position to 0
  myservo.attach(9);  //the pin for the servo control

  Serial.println("direct_servo_test"); 

} 

void loop() 
{   
  while (Serial.available()) {
    char c = Serial.read();  //gets one byte from serial buffer
    readString += c; //makes the string readString
    delay(2);  // allow buffer to fill with next character
  }

  if (readString.length() >0) {
    Serial.println(readString);  //so you can see the captured string 
    int n = readString.toInt();
    myservo.write(n); //convert readString to number for servo
    readString=""; //empty for next input
  } 
} 

