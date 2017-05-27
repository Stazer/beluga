#pragma once

#include <beluga/http/http_version.hpp>
#include <beluga/http/http_headers.hpp>

namespace beluga
{
    class http_response
    {
    public:
	http_response(http_version version = http_version::UNKNOWN, const http_headers& headers = http_headers());

	void set_version(http_version version);
	http_version get_version() const;
	
	void set_headers(const http_headers& headers);
	http_headers& get_headers();
	const http_headers& get_headers() const;
	
    private:
	http_version version;
	http_headers headers;
    };
}
