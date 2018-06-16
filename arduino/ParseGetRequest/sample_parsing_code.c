//Use this at this site:
//https://www.tutorialspoint.com/c_standard_library/c_function_sscanf.htm
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char first_line[20];

char* appending(char *cArr, const char c)
{
    int len = strlen(cArr);
    cArr[len + 1] = cArr[len];
    cArr[len] = c;
return cArr;

}

int main () {
    int x,y;
char *word = "Foobar";
// != '\0' is not required, but more readable

for(int i = 0; word[i] != '\0'; i++) {
    appending(*first_line,word[i]);


    printf("%c", word[i]);

}
    printf("first_line:%s",first_line);
   char type[20], path[20], protocol[100], dtm[200],dummy1[20],dummy2[20];

   strcpy( dtm, "GET /?x=123&y=177 HTTP/1.1" );
   //strcpy( dtm, "apple xf5kyj8 HTTP/1.1" );
   sscanf( dtm, "%s %s %s", type, path, protocol );

   printf("%s %s, %s \n", type, path, protocol );
    
   sscanf(path,"%4s%d%3s%d",dummy1,&x,dummy2,&y);
    //sscanf("sddf4711bar", "%s%d%s", dummy2,&x, dummy1);
   printf("I found %d and %d\n",x,y);
   return(0);
}