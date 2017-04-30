#include <beluga/http/http_method.hpp>
#include <boost/algorithm/string.hpp>

beluga::http_method beluga::to_http_method(const std::string& string)
{
    std::string temp = boost::to_upper_copy<std::string>(string);

    if(temp == "GET")
	return http_method::GET;
    else if(temp == "POST")
	return http_method::POST;
    else if(temp == "HEAD")
	return http_method::HEAD;
    else if(temp == "PATCH")
	return http_method::PATCH;
    else if(temp == "PUT")
	return http_method::PUT;
    else if(temp == "DELETE")
	return http_method::DELETE;
    else if(temp == "CONNECT")
	return http_method::CONNECT;
    else if(temp == "OPTIONS")
	return http_method::OPTIONS;
    else if(temp == "TRACE")
	return http_method::TRACE;

    return http_method::UNKNOWN;
}
std::string beluga::to_string(http_method method)
{
    switch(method)
    {
    case http_method::GET:
	return "GET";

    case http_method::POST:
	return "POST";

    case http_method::HEAD:
	return "HEAD";

    case http_method::PATCH:
	return "PATCH";

    case http_method::PUT:
	return "PUT";

    case http_method::DELETE:
	return "DELETE";

    case http_method::CONNECT:
	return "CONNECT";

    case http_method::OPTIONS:
	return "OPTIONS";

    case http_method::TRACE:
	return "TRACE";
    }

    return "";
}

