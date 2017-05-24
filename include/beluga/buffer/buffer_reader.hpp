#pragma once

#include <cstdint>

namespace beluga
{
    template <typename iterator_type>
    class buffer_reader
    {
    public:
	buffer_reader(iterator_type from, iterator_type to);
	buffer_reader(iterator_type from, iterator_type to, iterator_type iterator);

	virtual ~buffer_reader() = default;

	void set_from(iterator_type iterator);
	iterator_type get_from() const;
	
	void set_to(iterator_type to);
	iterator_type get_to() const;

	void set_iterator(iterator_type iterator);
	iterator_type get_iterator() const;

	std::size_t get_length() const;

	std::size_t get_available_length() const;
	std::size_t has_minimum_length(std::size_t length) const;
	
	std::uint8_t read_byte();
	void read_byte(std::uint8_t& byte);

	void read_bytes(std::uint16_t& bytes);
	void read_bytes(std::uint32_t& bytes);	
	void read_bytes(std::uint64_t& bytes);
	template <typename bytes_type>
	void read_bytes(bytes_type& bytes, std::uint8_t amount);
	
	template <typename input_iterator_type>
	void read_byte_array(input_iterator_type iterator, std::size_t amount);
	template <typename container_type>
	void read_byte_array(container_type& bytes);
	
	// todo
	buffer_reader<iterator_type>& operator >>(std::uint8_t& byte);
	buffer_reader<iterator_type>& operator >>(std::uint16_t& bytes);
	buffer_reader<iterator_type>& operator >>(std::uint32_t& bytes);
	buffer_reader<iterator_type>& operator >>(std::uint64_t& bytes);
	template <typename container_type>
	buffer_reader<iterator_type>& operator >>(container_type& bytes);
	    
    private:
	iterator_type from;
	iterator_type to;
	
	iterator_type iterator;
    };
}

#include <beluga/buffer/buffer_reader.inl>
