#pragma once

#include <string>

namespace beluga
{
    enum class http_method
    {
	GET,
	POST,
	HEAD,
	PATCH,
	PUT,
	DELETE,
	CONNECT,
	OPTIONS,
	TRACE,	

	UNKNOWN
    };

    http_method to_http_method(const std::string& string);
    std::string to_string(http_method method);
 }
