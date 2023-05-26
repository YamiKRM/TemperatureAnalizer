#pragma once

#include <vector>

#ifndef _REQUESTS
#define _REQUESTS
#endif // !_RQEST


#define GET "GET"
#define POST "POST"

#define API_KEY "BBFF-be5ac80954fb00ed9a19b784241fc9ef47f"
#define API_TOKEN_REQUEST "http://industrial.api.ubidots.com/api/v1.6/auth/token"

typedef std::vector<std::pair<std::string, std::string>> HEADERS;

namespace requests
{

	void get_request(const char* url);

	void post_request(const char* url, HEADERS &headers);

}