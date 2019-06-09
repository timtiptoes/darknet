


// Chapter 7 - Communications
// I2C Slave
// By Cornel Amariei for Packt Publishing

// Include the required Wire library for I2C
#include <Wire.h>
#include <stdio.h>
#include <string.h>
#include <Servo.h> 
//#include <tim_math.h>

int LED = 13;
int x0=0,y0=0,x1=0,y1=0,xs,ys,xold,yold;

char recd_string[7] ="";
char old_recd_string[7]="";
char c;
int i;
Servo myservo;

Servo myxservo; 
Servo myyservo;

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
  x0=9;y0=170;
  x1=153;y1=32;
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

  myxservo.write(0); //set initial servo position to 0
  myxservo.attach(9);

  myyservo.write(0);
  myyservo.attach(10);
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

    xs=result.x;
    //xs=map(result.x,0,640,x1,x0);
    if (xs!=xold){
      //myservo. attach(9);
     //delay(200);

      myxservo.write(xs); //convert readString to number for servo
      xold=xs;
      //delay(200);
      //myservo.detach();
      Serial.print("Moved x to ");
      Serial.println(xs);
    }
         

    //ys=map(result.y,0,480,y1,y0);
    ys=result.y;
    if (ys!=yold){
      //myyservo.attach(10);
     // delay(200);

      myyservo.write(ys); //convert readString to number for servo
//      delay(200);
  //    myservo.detach();
      yold=ys;
      Serial.print("Moved y to ");
      Serial.println(ys);

  }

   delay(2000);
}
}
