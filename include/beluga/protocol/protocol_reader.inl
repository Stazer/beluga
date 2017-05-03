template <typename iterator_type>
template <typename container_type>
beluga::protocol_reader<iterator_type>::protocol_reader(const container_type& container):
    protocol_reader(std::begin(container), std::end(container))
{
}
template <typename iterator_type>
beluga::protocol_reader<iterator_type>::protocol_reader(iterator_type from, iterator_type to):
    reader(from),
    from(from),
    to(to)
{
}

template <typename iterator_type>
bool beluga::protocol_reader<iterator_type>::has_minimum_length(std::size_t length) const
{
    return (to - reader.get_iterator()) >= length;
}

template <typename iterator_type>
template <typename container_type>
bool beluga::protocol_reader<iterator_type>::has_delimiter(const container_type& container) const
{
    return has_delimiter(std::begin(container), std::end(container));
}
template <typename iterator_type>
bool beluga::protocol_reader<iterator_type>::has_delimiter(iterator_type from, iterator_type to) const
{
    return std::search(get_reader().get_iterator(), this->to, from, to) != to;
}

template <typename iterator_type>
beluga::buffer_reader<iterator_type>& beluga::protocol_reader<iterator_type>::get_reader()
{
    return reader;
}

template <typename iterator_type>
iterator_type beluga::protocol_reader<iterator_type>::get_from()
{
    return from;
}
template <typename iterator_type>
iterator_type beluga::protocol_reader<iterator_type>::get_to()
{
    return to;
}
