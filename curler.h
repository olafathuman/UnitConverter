#include <string>
#include <curl/curl.h>
#include <iostream>
#ifndef CURLER_H
#define CURLER_H


class Curler{
    public:
    static size_t WriteCallback(char *wd, size_t size, size_t nmemb, std::string *stream){
        size_t actualSize = size*nmemb;
        stream->append(wd,actualSize);
        return 0;
    }
static std::string getStuff(){
    using namespace std;
    CURL *curl;
    string readBuffer;

    curl = curl_easy_init();
    if(curl){
    curl_easy_setopt(curl, CURLOPT_URL,"http://api.fixer.io/latest");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    curl_easy_setopt(curl, CURLOPT_HTTPGET,new long);
    curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    }
    return readBuffer;
}
};
#endif
