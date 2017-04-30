#pragma once

#include <beluga/protocol/protocol_reader.hpp>

namespace beluga
{
    template <typename iterator_type>
    class tls_reader : public protocol_reader<iterator_type>
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
    };    
}

#include <beluga/tls/tls_reader.inl>
