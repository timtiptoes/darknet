#include <Wire.h>
#include <stdlib.h>
#include <stdio.h>
#include <tims_utils.h>

String readString;

void setup() {
  init_serial(Serial);
  Wire.begin();

}

  void loop() 
{   
  readString=fetch_kbd_string(Serial);
  int n = readString.length(); 
  if (n >0) {
    Serial.println(readString); 
    transmit_coordinates(Wire,readString);
    readString=""; 
  } 
} 
