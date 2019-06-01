// Chapter 7 - Communications
// I2C Slave
// By Cornel Amariei for Packt Publishing

// Include the required Wire library for I2C
#include <Wire.h>
#include <stdio.h>
#include <string.h>


int LED = 13;
char recd_string[7] ="";
char old_recd_string[7]="";
char c;
int i;

void append(char* s, char c)
{
        int len = strlen(s);
        s[len] = c;
        s[len+1] = '\0';
}

struct pair {
    int x;
    int y;
};

struct pair convert_string(char* inputString)
{
  char now_string[20]="";
  char *ptr;
  ptr = strtok(inputString, ",");
  int i=0;
  int x;
  int y;
  while(ptr != NULL)
    {
      sprintf(now_string,"%s", ptr);
      if(i==0){
          sscanf(now_string,"%d",&x);
          i++;}
      else if (i==1){sscanf(now_string,"%d",&y);}
      ptr = strtok(NULL, ",");

    }
  struct pair r = {x,y};
return r;
}


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
}

void receiveEvent(int howmany) {
  memset(recd_string, 0, 7);
  while (1 < Wire.available()) { // loop through all but the last
    c = Wire.read(); // receive byte as a character
    append(recd_string,c);
    //Serial.print(c);         // print the character
  }
  int x = Wire.read();    // receive byte as an integer
  c=x;
  append(recd_string,c);

}

void loop() {
  if (recd_string!=old_recd_string){
    
    struct pair result=convert_string(recd_string);
    
    strcpy(old_recd_string,recd_string);
    Serial.print(result.x);
    Serial.print("----");
    Serial.println(result.y);
    delay(5000);
  }
}
