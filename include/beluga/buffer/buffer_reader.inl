template <typename iterator_type>
beluga::buffer_reader<iterator_type>::buffer_reader(iterator_type from, iterator_type to):
    buffer_reader<iterator_type>(from, to, from)
{
}

template <typename iterator_type>
beluga::buffer_reader<iterator_type>::buffer_reader(iterator_type from, iterator_type to, iterator_type iterator):
    from(from),
    to(to),
    iterator(iterator)
{
}

template <typename iterator_type>
void beluga::buffer_reader<iterator_type>::set_from(iterator_type from)
{
    this->from = from;
}
template <typename iterator_type>
iterator_type beluga::buffer_reader<iterator_type>::get_from() const
{
    return from;
}

template <typename iterator_type>
void beluga::buffer_reader<iterator_type>::set_to(iterator_type to)
{
    this->to = to;
}
template <typename iterator_type>
iterator_type beluga::buffer_reader<iterator_type>::get_to() const
{
    return to;
}

template <typename iterator_type>
void beluga::buffer_reader<iterator_type>::set_iterator(iterator_type iterator)
{
    this->iterator = iterator;
}
template <typename iterator_type>
iterator_type beluga::buffer_reader<iterator_type>::get_iterator() const
{
    return iterator;
}

template <typename iterator_type>
std::size_t beluga::buffer_reader<iterator_type>::get_length() const
{
    return to - from;
}

template <typename iterator_type>
std::size_t beluga::buffer_reader<iterator_type>::get_available_length() const
{
    return to - iterator;
}
template <typename iterator_type>
std::size_t beluga::buffer_reader<iterator_type>::has_minimum_length(std::size_t length) const
{
    return get_available_length() >= length;
}

template <typename iterator_type>
std::uint8_t beluga::buffer_reader<iterator_type>::read_byte()
{
    return *(iterator++);
}

template <typename iterator_type>
void beluga::buffer_reader<iterator_type>::read_byte(std::uint8_t& byte)
{
    byte = read_byte();
}

template <typename iterator_type>
void beluga::buffer_reader<iterator_type>::read_bytes(std::uint16_t& bytes)
{
    bytes = (read_byte() << 8) | read_byte();
}

template <typename iterator_type>
void beluga::buffer_reader<iterator_type>::read_bytes(std::uint32_t& bytes)
{
    bytes = (read_byte() << 24) |
	(read_byte() << 16) |
	(read_byte() << 8) |
	read_byte();
}

template <typename iterator_type>
void beluga::buffer_reader<iterator_type>::read_bytes(std::uint64_t& bytes)
{
    bytes = (read_bytes() << 56) |
	(read_byte() << 48) |
	(read_byte() << 32) |
	(read_byte() << 24) |
	(read_byte() << 16) |
	(read_byte() << 8) |
	read_byte();
}

template <typename iterator_type>
template <typename bytes_type>
void beluga::buffer_reader<iterator_type>::read_bytes(bytes_type& bytes, std::uint8_t amount)
{
    while(amount > 0)
	bytes = bytes | (read_byte() << --amount * 8);
}

template <typename iterator_type>
template <typename input_iterator_type>
void beluga::buffer_reader<iterator_type>::read_byte_array(input_iterator_type iterator, std::size_t amount)
{
    for(std::size_t i = 0; i < amount; ++i)
	*(iterator++) = read_byte();
}

template <typename iterator_type>
template <typename container_type>
void beluga::buffer_reader<iterator_type>::read_byte_array(container_type& bytes)
{
    read_byte_array(bytes.begin(), bytes.size());
}

template <typename iterator_type>
beluga::buffer_reader<iterator_type>& beluga::buffer_reader<iterator_type>::operator >>(std::uint8_t& byte)
{
    read_byte(byte);
    return *this;
}

template <typename iterator_type>
beluga::buffer_reader<iterator_type>& beluga::buffer_reader<iterator_type>::operator >>(std::uint16_t& bytes)
{
    read_bytes(bytes);
    return *this;
}

template <typename iterator_type>
beluga::buffer_reader<iterator_type>& beluga::buffer_reader<iterator_type>::operator >>(std::uint32_t& bytes)
{
    read_bytes(bytes);
    return *this;
}

template <typename iterator_type>
beluga::buffer_reader<iterator_type>& beluga::buffer_reader<iterator_type>::operator >>(std::uint64_t& bytes)
{
    read_bytes(bytes);
    return *this;
}
template <typename iterator_type>
template <typename container_type>
beluga::buffer_reader<iterator_type>& beluga::buffer_reader<iterator_type>::operator >>(container_type& bytes)
{
    read_byte_array(bytes);
    return *this;
}
