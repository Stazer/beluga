#pragma once

namespace beluga
{
    template <typename iterator_type>
    class tls_reader
    {
    public:
	template <typename container_type>
	tls_reader(const container_type& container);	
	tls_reader(iterator_type from, iterator_type to);
	
	bool read_record(tls_record& record, bool check_length = true);
	bool read_handshake(tls_handshake& handshake, bool check_length = true);	
	bool read_client_hello(tls_client_hello& client_hello, bool check_length = true);

	bool read_session_id(std::uint64_t& session_id, bool check_length = true);
	bool read_cipher_suites(tls_client_hello::cipher_suites_type& cipher_suites, bool check_length = true);
	bool read_compression_methods(tls_client_hello::compression_methods_type& compression_methods, bool check_length = true);
	bool read_extensions(tls_client_hello::extensions_type& extensions, bool check_length = true);
	
	bool has_minimum_length(std::size_t length);
	
    private:
	buffer_reader<iterator_type> reader;
	iterator_type to;
    };    
}

#include <beluga/tls/tls_reader.inl>
