#pragma once

#include <beluga/buffer/buffer_reader.hpp>
#include <boost/algorithm/string.hpp>

namespace beluga
{
    template <typename iterator_type>
    class http_reader : public buffer_reader<iterator_type>
    {
    public:
	template <typename container_type>
	http_reader(const container_type& container);
	http_reader(iterator_type from, iterator_type to);
	
	bool read_request(http_request& request);

	bool read_request_line(http_method& method, std::string& uri, http_version& version);
	bool read_headers(http_headers& headers);
    };
}

#include <beluga/http/http_reader.inl>
