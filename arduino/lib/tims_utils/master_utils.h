

void init_serial(HardwareSerial serial){
  while (!serial) {
    ; // wait for serial port to connect.
  }
  serial.begin(9600);
  Serial.println("Setup complete inside dot H file!!");
}

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

void transmit_coordinates(TwoWire wire,String rs){
    char char_array[rs.length() + 1]; 
    strcpy(char_array, rs.c_str()); 
    wire.beginTransmission(9); // transmit to device #9
    wire.write(char_array);              // sends x
    wire.endTransmission();    // stop transmitting
}

String fetch_kbd_string(HardwareSerial serial){
    String rs;
    while (Serial.available()) {
    char c = Serial.read();  //gets one byte from serial buffer
    rs += c; //makes the string readString
    delay(2);  // allow buffer to fill with next character
  }
  return rs;
}

struct pair get_pot_reading(HardwareSerial serial)
{
  int xValue,yValue,xs_old=0,xs,ys,ys_old=0;
  button1State = digitalRead(2);
  xValue = analogRead(xPin);  
  yValue = analogRead(yPin);

  
  while(button1State == HIGH){
    xValue = analogRead(xPin);  
    yValue = analogRead(yPin);

    button1State = digitalRead(2);
    xs=map(xValue,0,1023,0,180);
    if ((abs(xs-xs_old)>5)){
      myxservo.write(xs);
      xs_old=xs;
    }
    ys=map(yValue,0,1023,0,180);
    if ((abs(ys-ys_old)>5)){
      myyservo.write(ys);
      ys_old=ys;
    }
  }
  pair r = {xs_old,ys_old};
  Serial.println("Just sent these corners:");
serial.print(xs);
serial.print(",");
serial.println(ys);
return r;
}

void init_wifli(){

  uart.begin(9600);

  Serial.begin(9600);
  Serial.println("--------- Web Servo Control --------");

  // wait for initialization of wifly
  delay(3000);

  uart.begin(9600);     // WiFly UART Baud Rate: 9600

  wifly.reset();
  delay(1000);


  wifly.sendCommand("set ip local 80\r"); // set the local comm port to 80
  delay(100);

  wifly.sendCommand("set comm remote 0\r"); // do not send a default string when a connection opens
  delay(100);

  wifly.sendCommand("set comm open *OPEN*\r"); // set the string that the wifi shield will output when a connection is opened
  delay(100);

  Serial.println("Join " SSID );
  if (wifly.join(SSID, KEY, AUTH)) {
    Serial.println("OK");
  } 
  else {
    Serial.println("Failed");
  }
  delay(5000);

  wifly.sendCommand("get ip\r");
  uart.setTimeout(500);
  if(!uart.find("IP="))
  {
    Serial.println("can not get ip");
    while(1);
    ;
  }
  else
  {
    Serial.print("IP:");
  }

  char c;
  int index = 0;
  while (wifly.receive((uint8_t *)&c, 1, 300) > 0) { // print the response from the get ip command
    if(c == ':')
    {
      ip[index] = 0;
      break;
    }
    ip[index++] = c;
    Serial.print((char)c);

  }
  Serial.println();
  while (wifly.receive((uint8_t *)&c, 1, 300) > 0);
  ;
  
  Serial.println("Web server ready");
  wifly.sendCommand("set comm idle 4");
}



/*
void
send_coords(unsigned int x, unsigned int y){
  char out_string[30]="";
  sprintf(out_string, "%03d,%03d", x,y);
  Wire.beginTransmission(9); // transmit to device #9
  Wire.write(out_string);              // sends x
  Wire.endTransmission();    // stop transmitting
  return;
}
*/