#pragma once
#include <vector>

#include "HTTPRequest.hpp"
#include "BuffReader.h"

#ifndef _REQUESTS
#define _REQUESTS
#endif // !_RQEST

#define API_KEY "BBFF-be5ac80954fb00ed9a19b784241fc9ef47f"

#define API_TOKEN_REQUEST "http://industrial.api.ubidots.com/api/v1.6/auth/token"
#define TEMPERATURE_REQUEST "http://industrial.api.ubidots.com/api/v1.6/devices/esp/temperature/lv"


typedef std::vector<std::pair<std::string, std::string>> HEADERS;

#pragma comment(lib, "ws2_32.lib") //Add WinSock2.h

namespace requests
{

	http::Response get_request(const char* url, HEADERS& headers);

	http::Response post_request(const char* url, HEADERS &headers);

	void get_response_value(const http::Response& response, BuffReader* reader);

}
