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
	
	using iterator = map_type::iterator;
	using const_iterator = map_type::const_iterator;
	
	http_headers(const map_type& map = map_type());

	mapped_type& operator[](const key_type& key); 

	iterator begin();
	const_iterator begin() const;
	const_iterator cbegin() const;

	iterator end();
	const_iterator end() const;
	const_iterator cend() const;
	
    private:
	map_type map;
    };
}
