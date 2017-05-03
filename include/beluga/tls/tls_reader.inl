template <typename iterator_type>
template <typename container_type>
beluga::tls_reader<iterator_type>::tls_reader(const container_type& container):
    protocol_reader<iterator_type>(container)
{
}
template <typename iterator_type>
beluga::tls_reader<iterator_type>::tls_reader(iterator_type from, iterator_type to):
    protocol_reader<iterator_type>(from, to)
{		
}

template <typename iterator_type>
bool beluga::tls_reader<iterator_type>::read_record(tls_record& record)
{
    if(!this->has_minimum_length(5))
	return false;
    
    std::uint8_t type = 0;
    std::uint16_t version = 0, length = 0;
    
    this->get_reader() >> type >> version >> length;
    
    record.set_type(type);
    record.set_version(version);
    record.set_length(length);
    
    return true;
}

template <typename iterator_type>
bool beluga::tls_reader<iterator_type>::read_handshake(tls_handshake& handshake)
{
    if(!this->has_minimum_length(6))
	return false;
    
    std::uint8_t type = 0;
    std::uint64_t length = 0;
    
    this->get_reader() >> type;
    this->get_reader().read_bytes(length, 3);
    
    handshake.set_type(type);
    handshake.set_length(length);
    
    return true;
}

template <typename iterator_type>
bool beluga::tls_reader<iterator_type>::read_client_hello(tls_client_hello& client_hello)
{
    if(!this->has_minimum_length(35))
	return false;
    
    std::uint16_t version = 0;
    std::uint32_t gmt_unix_time = 0;
    tls_client_hello::random_bytes_type random_bytes;
    
    std::uint64_t session_id = 0;
    tls_client_hello::cipher_suites_type cipher_suites;
    tls_client_hello::compression_methods_type compression_methods;
    tls_client_hello::extensions_type extensions;
    
    this->get_reader() >> version >> gmt_unix_time >> random_bytes;

    if(!read_session_id(session_id) ||
       !read_cipher_suites(cipher_suites) ||
       !read_compression_methods(compression_methods) ||
       !read_extensions(extensions))
	return false;
   
    client_hello.set_version(version);
    client_hello.set_gmt_unix_time(gmt_unix_time);
    client_hello.set_random_bytes(random_bytes);
    client_hello.set_session_id(session_id);
    client_hello.set_cipher_suites(cipher_suites);
    client_hello.set_compression_methods(compression_methods);
    client_hello.set_extensions(extensions);
    
    return true;
}

template <typename iterator_type>
bool beluga::tls_reader<iterator_type>::read_session_id(std::uint64_t& session_id)
{
    if(!this->has_minimum_length(1))
	return false;
    
    std::uint8_t session_id_length = 0;

    this->get_reader() >> session_id_length;
    
    if(!this->has_minimum_length(session_id_length))
	return false;
    
    this->get_reader().read_bytes(session_id, session_id_length);	

    return true;
}

template <typename iterator_type>
bool beluga::tls_reader<iterator_type>::read_cipher_suites(tls_client_hello::cipher_suites_type& cipher_suites)
{
    if(!this->has_minimum_length(2))
	return false;
    
    std::uint16_t cipher_suites_length = 0;
    
    this->get_reader() >> cipher_suites_length;
    
    if(!this->has_minimum_length(cipher_suites_length))
	return false;
    
    cipher_suites.reserve(cipher_suites_length / 2);
    
    for(std::uint16_t i = 0; i < cipher_suites_length / 2; ++i)
    {
	std::uint16_t cipher_suite = 0;
	this->get_reader() >> cipher_suite;
	cipher_suites.push_back(cipher_suite);
    }

    return true;
}
template <typename iterator_type>
bool beluga::tls_reader<iterator_type>::read_compression_methods(tls_client_hello::compression_methods_type& compression_methods)
{ 
    if(!this->has_minimum_length(1))
	return false;
    
    std::uint8_t compression_methods_length = 0;
    
    this->get_reader() >> compression_methods_length;
    
    if(!this->has_minimum_length(compression_methods_length))
	return false;
    
    for(std::uint8_t i = 0; i < compression_methods_length; ++i)
    {
	std::uint8_t compression_method = 0;
	this->get_reader() >> compression_method;
	compression_methods.push_back(compression_method);
    }

    return true;
}
template <typename iterator_type>
bool beluga::tls_reader<iterator_type>::read_extensions(tls_client_hello::extensions_type& extensions)
{
    if(!this->has_minimum_length(2))
	return false;
    
    std::uint16_t extensions_length = 0;

    this->get_reader() >> extensions_length;
    
    if(!this->has_minimum_length(extensions_length))
	return false;
    
    while(extensions_length > 0)
    {
	if(!this->has_minimum_length(4))
	    return false;
	
	std::uint16_t type = 0, length = 0;
	this->get_reader() >> type >> length;
	
	if(!this->has_minimum_length(length))
	    return false;
	
	tls_extension::data_type data;
	data.resize(length, 0);
	this->get_reader() >> data;
	
	extensions.push_back(tls_extension(type, data));
	
	extensions_length -= (4 + length);
    }

    return true;
}
