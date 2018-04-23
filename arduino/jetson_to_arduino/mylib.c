#include <stdio.h>
#include <curl/curl.h>
#include <string.h>
/*gcc -o mylib.o -c mylib.c -lcurl */



int send_coords(char *msg)
{
  CURL *curl;
  CURLcode res;
  char str[200];
	printf("just want you to know that I got %s",msg);
  curl = curl_easy_init();
  if(curl) {
	printf("I made it in here %s",msg);
    strcpy(str,"http://192.168.1.175/?msg=");
    curl_easy_setopt(curl, CURLOPT_URL, strcat(str,msg));
    /* example.com is redirected, so we tell libcurl to follow redirection */ 
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
 
    /* Perform the request, res will get the return code */ 
    res = curl_easy_perform(curl);
    /* Check for errors */ 
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
 
    /* always cleanup */ 
    curl_easy_cleanup(curl);
  }
  return 0;
}


