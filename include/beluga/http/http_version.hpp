#pragma once

#include <string>

namespace beluga
{
    enum class http_version
    {
	_1_0,
	_1_1,
	_2_0,
	    
	UNKNOWN,
    };

    http_version to_http_version(const std::string& string);
    std::string to_string(http_version version);
}
