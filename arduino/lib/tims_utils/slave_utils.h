

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

void move_servo(struct pair pr)
{
	myxservo.write(pr.x);
    myyservo.write(pr.y);
    Serial.println("Just moved to ");
	Serial.print(pr.x);
	Serial.print(",");
	Serial.println(pr.y);
return;
}

void append(char* s, char c)
{
        int len = strlen(s);
        s[len] = c;
        s[len+1] = '\0';
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
