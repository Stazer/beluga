#include <beluga/http/http_request.hpp>

beluga::http_request::http_request(http_method method, const std::string& uri, http_version version, const beluga::http_headers& headers):
    method(method),
    uri(uri),
    version(version),
    headers(headers)
{
}

void beluga::http_request::set_method(http_method method)
{
    this->method = method;
}
beluga::http_method beluga::http_request::get_method() const
{
    return method;
}
    
void beluga::http_request::set_uri(const std::string& uri)
{
    this->uri = uri;
}
const std::string& beluga::http_request::get_uri() const
{
    return uri;
}
    
void beluga::http_request::set_version(http_version version)
{
    this->version = version;
}
beluga::http_version beluga::http_request::get_version() const
{
    return version;
}

void beluga::http_request::set_headers(const http_headers& headers)
{
    this->headers = headers;
}
beluga::http_headers& beluga::http_request::get_headers()
{
    return headers;
}
const beluga::http_headers& beluga::http_request::get_headers() const
{
    return headers;
}
