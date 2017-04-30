#include <beluga/http/http_version.hpp>
#include <boost/algorithm/string.hpp>

beluga::http_version beluga::to_http_version(const std::string& string)
{
    std::string temp = boost::to_upper_copy<std::string>(string);

    if(temp == "HTTP/1.0")
	return beluga::http_version::HTTP_1_0;
    else if(temp == "HTTP/1.1")
	return beluga::http_version::HTTP_1_1;
    else if(temp == "HTTP/2.0")
	return beluga::http_version::HTTP_2_0;

    return beluga::http_version::UNKNOWN;
}
std::string beluga::to_string(http_version version)
{
    switch(version)
    {
    case beluga::http_version::HTTP_1_0:
	return "HTTP/1.0";
	
    case beluga::http_version::HTTP_1_1:
	return "HTTP/1.1";

    case beluga::http_version::HTTP_2_0:
	return "HTTP/2.0";
    }

    return "";
}
