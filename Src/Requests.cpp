#include <iostream>

#include "Requests.h"
#include "HTTPRequest.hpp"

#pragma comment(lib, "ws2_32.lib") //Add WinSock2.h

void requests::get_request(const char* url)
{

    try
    {

        // you can pass http::InternetProtocol::V6 to Request to make an IPv6 request
        http::Request request{ url };

        // send a the request
        const auto response = request.send(GET);

        //Print the result
        std::cout << std::string{ response.body.begin(), response.body.end() } << '\n'; 

    }
    catch (const std::exception& e)
    {

        std::cerr << "Request failed, error: " << e.what() << '\n';

    }

}


void requests::post_request(const char* url, HEADERS &headers)
{

    try
    {

        // you can pass http::InternetProtocol::V6 to Request to make an IPv6 request
        http::Request request{ url };

        // send a the request
        const auto response = request.send(POST, "", headers);

        //Print the result
        std::cout << std::string{ response.body.begin(), response.body.end() } << '\n';

    }
    catch (const std::exception& e)
    {

        std::cerr << "Request failed, error: " << e.what() << '\n';

    }

}