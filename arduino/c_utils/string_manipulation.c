#include <stdio.h>
#include <string.h>
#include <stdlib.h> // For random(), RAND_MAX

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

int main()
{
char out_string[30]="";
  // send an intro:
printf("\n\nString toInt():");
int i;
char inString[20]="3948";
sscanf(inString, "%d", &i);

printf("Value:");
printf("%d\n",i);

printf("String: ");
printf("%s\n",inString);
int x;
int y;
int a;
for( a = 10; a < 20; a = a + 1 ){

  x = randr(0,180);
  y = randr(0,180);
  sprintf(out_string, "(%03d,%03d)", x,y);
  printf("%s\n",out_string);

  struct pair rr = convert_string(out_string);
}
return 0;
} 



