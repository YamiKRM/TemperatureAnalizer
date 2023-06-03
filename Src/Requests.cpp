#include <iostream>

#include "Requests.h"

#define DOUBLE_DOTS 58
#define DOUBLE_QUOTES 34

http::Response requests::get_request(const char* url, HEADERS& headers)
{

    try
    {

        // you can pass http::InternetProtocol::V6 to Request to make an IPv6 request
        http::Request request{ url };

        // send a the request
        const auto response = request.send("GET", "", headers);

        return response;

        //Print the result
        //std::cout << std::string{ response.body.begin(), response.body.end() } << '\n'; 

    }
    catch (const std::exception& e)
    {

        std::cerr << "Request failed, error: " << e.what() << '\n';

    }

}


http::Response requests::post_request(const char* url, HEADERS& headers)
{

    try
    {

        // you can pass http::InternetProtocol::V6 to Request to make an IPv6 request
        http::Request request{ url };

        // send a the request
        const auto response = request.send("POST", "", headers);

        return response;

        //Print the result
        //std::cout << std::string{ response.body.begin(), response.body.end() } << '\n';

    }
    catch (const std::exception& e)
    {

        std::cerr << "Request failed, error: " << e.what() << '\n';

    }

}


void requests::get_response_value(const http::Response& response, BuffReader* reader)
{
    
    uint8_t* buffer_start = nullptr;
    size_t buffer_length = 1;

    //Read the response buffer to get the value location
    for (int i = 0; i < response.body.size(); i++)
    {
        
        const uint8_t current_value = response.body[i];
        
        if (current_value == DOUBLE_DOTS)
        {

            buffer_start = (uint8_t*)(&response.body[i] + 3);
            i += 3;

            continue;

        }

        if (buffer_start != NULL)
            buffer_length++;
             

        if (current_value == DOUBLE_QUOTES && buffer_start != NULL)
        {

            buffer_length--;
            break;

        }


    }

    if (buffer_start == nullptr)
    {
        
        buffer_start = (uint8_t*)&response.body[0];
        buffer_length = response.body.size();

    }

    //Pass the buffer to the buffer reader class

    reader->change_buff(buffer_start, buffer_length);


}
