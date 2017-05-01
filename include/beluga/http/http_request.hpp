#pragma once

#include <cstdint>
#include <string>
#include <beluga/http/http_method.hpp>
#include <beluga/http/http_version.hpp>
#include <beluga/http/http_headers.hpp>

namespace beluga
{
    class http_request
    {
    public:
	http_request(http_method method = http_method::UNKNOWN, const std::string& uri = "", http_version version = http_version::UNKNOWN, const http_headers& headers = http_headers());

	void set_method(http_method method);
	http_method get_method() const;

	void set_uri(const std::string& uri);
	const std::string& get_uri() const;
	
	void set_version(http_version version);
	http_version get_version() const;
	
	void set_headers(const http_headers& headers);
	http_headers& get_headers();
	const http_headers& get_headers() const;

    private:
	http_method method;
	std::string uri;
	http_version version;
	http_headers headers;
    };
}
