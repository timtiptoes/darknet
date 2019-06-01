// Chapter 7 - Communications
// I2C Master
// By Cornel Amariei for Packt Publishing

// Include the required Wire library for I2C
#include <Wire.h>
#include <stdlib.h>
#include <stdio.h>
//==============================
  String readString;

void setup() {
  Serial.begin(9600);
  Serial.println("Setup complete");
  Wire.begin();

}

  void loop() 
{   
  while (Serial.available()) {
    char c = Serial.read();  //gets one byte from serial buffer
    readString += c; //makes the string readString
    delay(2);  // allow buffer to fill with next character
  }

  int n = readString.length(); 

  if (n >0) {
    Serial.println(readString);  //so you can see the captured string 

    char char_array[n + 1]; 
    strcpy(char_array, readString.c_str()); 
    Serial.print("Sending:");
    Serial.println(char_array);
    Wire.beginTransmission(9); // transmit to device #9
    Wire.write(char_array);              // sends x
    Wire.endTransmission();    // stop transmitting
    readString=""; //empty for next input
  } 
} 
