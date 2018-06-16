
#include <Arduino.h>
#include <SoftwareSerial.h>
#include "WiFly.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SSID      "ATTxUERtUI"
#define KEY       "dontfear7thegipper8"
#define AUTH      WIFLY_AUTH_WPA2_PSK

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


