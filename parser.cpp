/***
   * std::string curl_process()
   *    make a GET request to API and return the result in std::string form
   *
   * std::size_t WriteMemoryCallback(char* , std::size_t, std::size_t, std::string)
   *    Function to store the contents of GET Request into MEMORY instead of stdout
   *
   * std::size_t write_data(void* , std::size_t, std::size_t, void*)
   *    Function to store the contents of GET request into FILE instead of stdout
***/

#include "parser.h"
#include <string>
#include <curl/curl.h>
#include <iostream>

std::size_t Parser::WriteMemoryCallback(char *in, std::size_t size, std::size_t nmemb, std::string *out)
{
    std::size_t total_size = size * nmemb;
    if(total_size)
    {
        out->append(in, total_size);
        return total_size;
    }
    return 0;
}

std::size_t write_data(void *ptr, std::size_t size, std::size_t nmemb, void *stream)
{
    std::size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);
    return written;
}

std::string Parser::curl_process()
{
    std::string str_buffer;
    CURL *curl_handler = curl_easy_init();
    CURLcode res;

    if(curl_handler)
    {
        curl_easy_setopt(curl_handler, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl_handler, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl_handler, CURLOPT_WRITEDATA, &str_buffer);
        res = curl_easy_perform(curl_handler);
        if(res != CURLE_OK)
        {
            std::cerr << " curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
            exit(1);
        } 
        else 
        {   
            curl_easy_cleanup(curl_handler);
            return str_buffer;
        } 
    }
    return ("Null");
}