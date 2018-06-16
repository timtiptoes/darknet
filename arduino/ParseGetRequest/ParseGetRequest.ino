
#include <Arduino.h>
#include <SoftwareSerial.h>
#include "WiFly.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SSID      "ATTxUERtUI"
#define KEY       "dontfear7thegipper8"
#define AUTH      WIFLY_AUTH_WPA2_PSK

/*
//https://www.dreamincode.net/forums/topic/222380-going-through-each-element-of-a-char-array-in-c/
//http://forum.codecall.net/topic/59761-iterating-through-a-char-in-c/
//https://stackoverflow.com/questions/10279718/append-char-to-string-in-c
//https://stackoverflow.com/questions/4823177/reading-a-file-character-by-character-in-c
//https://scienceprog.com/getting-hands-on-arduino-ethernet-shield/
//https://github.com/LambdaSchool/C-Web-Server/blob/solution/src/server.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main () {
    int i,x,y;
    char *first_line;
    char type[20], path[20], protocol[100], dtm[200],dummy1[20],dummy2[20];
    char str[] = "GET /?x=123&y=177 HTTP/1.1";
    size_t n = 0;

    first_line=malloc(1000);

    
    for(i = 0; str[i] != '\0'; ++i) {
        first_line[i] = str[i];
    }

    first_line[i] = '\0'; 
    

 //      while ((c = fgetc(file)) != EOF)
 //   {
 //       code[n++] = (char) c;
 //   }

//   strcpy( dtm, "GET /?x=123&y=177 HTTP/1.1" );
   //strcpy( dtm, "apple xf5kyj8 HTTP/1.1" );
   sscanf( first_line, "%s %s %s", type, path, protocol );
   printf("%s %s, %s \n", type, path, protocol );
    
   sscanf(path,"%4s%d%3s%d",dummy1,&x,dummy2,&y);
    //sscanf("sddf4711bar", "%s%d%s", dummy2,&x, dummy1);
   printf("I found %d and of course %d\n",x,y);
   return(0);
}

*/


char type[8]; // GET or POST
char path[1024]; // /info etc.
char protocol[128]; // HTTP/1.1
char c;
char first_line;


// Pins' connection
// Arduino       WiFly
//  2    <---->    TX
//  3    <---->    RX
SoftwareSerial uart(2, 3);
WiFly wifly(&uart);

void setup() {
  uart.begin(9600);

  Serial.begin(9600);
  Serial.println("--------- WIFLY TEST --------");
  
  // wait for initilization of wifly
  delay(3000);
  
  uart.begin(9600);     // WiFly UART Baud Rate: 9600
  
  wifly.reset();
  
  Serial.println("Join " SSID );
  if (wifly.join(SSID, KEY, AUTH)) {
    Serial.println("OK");
  } else {
    Serial.println("Failed");
  }
  
  // get WiFly params
  wifly.sendCommand("get everthing\r");
  char c;
  while (wifly.receive((uint8_t *)&c, 1, 300) > 0) {
    Serial.print((char)c);
  }
  
  if (wifly.commandMode()) {
    Serial.println("Enter command mode. Send \"exit\"(with \\r) to exit command mode");
  }
}

void loop() {
  while (wifly.available()) {
    Serial.write(wifly.read());
  }
  
  while (Serial.available()) {
    if(wiflyUart.find("*OPEN*")) // see if the data available is from an open connection by looking for the *OPEN* string
        {
          c=wiflyUart.read();
          while (c!='\n'){
            first_line+=c;
          }
          sscanf(first_line, "%s %s %s", type, path,protocol);
          wifly.write(request_path);
        }
          wifly.write(Serial.read());
   }
  }


