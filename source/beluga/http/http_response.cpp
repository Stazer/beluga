#include <beluga/http/http_response.hpp>

http_response(http_version version, const http_headers& headers):
    version(version),
    headers(headers)
{
}

void beluga::http_response::set_version(http_version version)
{
    this->version = version;
}
beluga::http_version beluga::http_response::get_version() const
{
    return version;
}

void beluga::http_response::set_headers(const http_headers& headers)
{
    this->headers = headers;
}
beluga::http_headers& beluga::http_response::get_headers()
{
    return headers;
}
const beluga::http_headers& beluga::http_response::get_headers() const
{
    return headers;
}
