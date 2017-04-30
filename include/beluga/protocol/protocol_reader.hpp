#pragma once

#include <beluga/buffer/buffer_reader.hpp>

namespace beluga
{
    template <typename iterator_type>
    class protocol_reader
    {
    public:
	template <typename container_type>
	protocol_reader(const container_type& container);	
	protocol_reader(iterator_type from, iterator_type to);

	virtual ~protocol_reader() = default;
	
	bool has_minimum_length(std::size_t length);

	buffer_reader<iterator_type>& get_reader();
	iterator_type get_to();
	
    private:
	buffer_reader<iterator_type> reader;
	iterator_type to;
    };    
}

#include <beluga/protocol/protocol_reader.inl>
