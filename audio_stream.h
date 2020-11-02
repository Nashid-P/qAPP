#ifndef __AUDIO_STREAM_H__
#define __AUDIO_STREAM_H__

#include <iostream>
#include "parser.h"

class audio_stream : public Parser
{
    private:
        std::string audio_url(int surah_number);
        static std::size_t play_stream(void *buffer, std::size_t size, std::size_t nmemb, void *userp);
    public:
        audio_stream(std::string url_str) 
        {
            this->url = url_str;
        }
        void process_stream();
};

#endif