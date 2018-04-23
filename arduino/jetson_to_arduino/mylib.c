#include <stdio.h>
#include <curl/curl.h>
#include <string.h>



int send_coords(char *msg)
{
  CURL *curl;
  CURLcode res;
  char str[80];
  curl = curl_easy_init();
  if(curl) {
    strcpy(str,"http://192.168.1.175/?msg=");
    curl_easy_setopt(curl, CURLOPT_URL, strcat(str,"doiles"));
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


