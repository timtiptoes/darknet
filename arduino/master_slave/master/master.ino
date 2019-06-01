// Chapter 7 - Communications
// I2C Master
// By Cornel Amariei for Packt Publishing

// Include the required Wire library for I2C
#include <Wire.h>
#include <stdlib.h>
#include <stdio.h>
//==============================
struct pair {
    int x;
    int y;
};

unsigned int
randr(unsigned int min, unsigned int max)
{
       double scaled = (double)rand()/RAND_MAX;

       return (max - min +1)*scaled + min;
}

struct pair convert_string(char* inputString)
{
  char now_string[20]="";
  int x=-9;
  int y=-9;
  char *ptr = strtok(inputString, ",");
  while(ptr != NULL)
    {
      sprintf(now_string,"%s", ptr);
      if(x==-9){sscanf(now_string,"%d",&x);}
      else{sscanf(now_string,"%d",&y);}
      ptr = strtok(NULL, ",");
    }
  struct pair r = {x,y};
return r;
}

void
send_coords(unsigned int x, unsigned int y){
  char out_string[30]="";
  sprintf(out_string, "%03d,%03d", x,y);
  Wire.beginTransmission(9); // transmit to device #9
  Wire.write(out_string);              // sends x
  Wire.endTransmission();    // stop transmitting
  return;
}

int x = 0;
int y = 0;



void setup() {
    Serial.begin(9600);
    Serial.println("Setup complete");

  // Start the I2C Bus as Master
  Wire.begin();

}

void loop() {
  char out_string[30]="";
  x = randr(0,180);
  y = randr(0,180);
  sprintf(out_string, "%03d,%03d", x,y);
  Serial.print("Transmitting:");
  Serial.println(out_string);
  Wire.beginTransmission(9); // transmit to device #9
  Wire.write(out_string);              // sends x
  Wire.endTransmission();    // stop transmitting
  delay(500);
}
