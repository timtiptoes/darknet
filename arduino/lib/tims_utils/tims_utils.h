

void init_serial(HardwareSerial serial){
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