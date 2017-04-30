#pragma once

#include <string>

namespace beluga
{
    enum class http_version
    {
	HTTP_1_0,
	HTTP_1_1,
	HTTP_2_0,
	    
	UNKNOWN,
    };

    http_version to_http_version(const std::string& string);
    std::string to_string(http_version version);
}
