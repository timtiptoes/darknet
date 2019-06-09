

// Chapter 7 - Communications
// I2C Master
// By Cornel Amariei for Packt Publishing

// Include the required Wire library for I2C
#include <Wire.h>
#include <stdlib.h>
#include <stdio.h>
#include <tims_utils.h>

int x = 0;
int y = 0;



void setup() {
  init_serial(Serial);
  Wire.begin();
}

void loop() {
  char out_string[7]="";
  x = randr(0,180);
  y = randr(0,180);
  sprintf(out_string, "%03d,%03d", x,y);
  Serial.print("Transmitting:");
  Serial.println(out_string);
  transmit_coordinates(Wire,out_string);

  delay(2000);
}
