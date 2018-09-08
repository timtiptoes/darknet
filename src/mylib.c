#include <stdio.h>
#include <curl/curl.h>
#include <string.h>
/*To compile module
  cd src
  gcc -o mylib.o -c mylib.c -lcurl 
  
And of course just 'make' to make darknet
*/


void send_coords(char* coordstr)
{
  CURL *curl;
  CURLcode res;
  char *location;
  char timsstr[200];

  curl = curl_easy_init();
  if(curl) {

    snprintf(timsstr,sizeof timsstr,"%s%s","http://192.168.1.125/?",coordstr);
	printf("Im really trying to get to %s",timsstr);
    curl_easy_setopt(curl, CURLOPT_URL,timsstr);
    /* example.com is redirected, so we tell libcurl to follow redirection */ 
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_VERBOSE,1L);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 0L);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT_MS, 1L);
    /* Perform the request, res will get the return code */ 
    res = curl_easy_perform(curl);
    /* Check for errors */ 
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
      res=curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &location);
      printf("Redirected to %s\n", location);
    /* always cleanup */ 
    curl_easy_cleanup(curl);
  }

}

void print_coords_to_file(char* labelstr,char* coordstr)
{
   if (strcmp(labelstr,"teddy bear")==0) 
    {
      FILE *f = fopen("points.txt", "a");
      if (f != NULL )
      {
         fprintf(f, "http://192.168.1.125/?%s\n", coordstr);
         fclose(f);
      }
    }
}
void send_coords_test(char *msg)
{
	printf("just want you to know that I got %s",msg);
}

