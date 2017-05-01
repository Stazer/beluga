#pragma once

#include <unordered_map>
#include <string>

namespace beluga
{
    class http_headers
    {
    public:
	using map_type = std::unordered_map<std::string, std::string>;
	using value_type = map_type::value_type;
	using key_type = map_type::key_type;
	using mapped_type = map_type::mapped_type;
	
	http_headers(const map_type& map = map_type());

	mapped_type& operator[](const key_type& key); 
	
    private:
	map_type map;
    };
}
