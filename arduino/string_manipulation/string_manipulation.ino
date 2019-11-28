#include <stdio.h>
#include <string.h>

struct pair {
    int x;
    int y;
};

struct pair convert_string(char* inputString)
{
  String now_string="";
  int x=-9;
  int y=-9;
  char *ptr = strtok(inputString, ",");
  while(ptr != NULL)
    {
      sprintf(now_string,"%s", ptr);
      if(x==-9){x=now_string.toInt();}
      else{y=now_string.toInt();}
      ptr = strtok(NULL, ",");
    }
  pair r = {x,y};
return r;
}
String inString = "";    // string to hold input

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  // send an intro:
  Serial.println("\n\nString toInt():");
  Serial.println();
}

void loop() {
  char out_string [10];
  // Read serial input:
  while (Serial.available() > 0) {
    int inChar = Serial.read();
    if (isDigit(inChar)) {
      // convert the incoming byte to a char 
      // and add it to the string:
      inString += (char)inChar; 
    }
    // if you get a newline, print the string,
    // then the string's value:
    if (inChar == '\n') {
      Serial.print("Value:");
      Serial.println(inString.toInt());
      Serial.print("String: ");
      Serial.println(inString);

    int x = 3;
    int y = 56;
    sprintf(out_string, ("%03d,%03d"), x,y);
    Serial.println(out_string);

    pair rr = convert_string(out_string);
     
      // clear the string for new input:
      inString = ""; 
    }
  }
}




