#pragma once

#include <cstdint>
#include <array>
#include <vector>
#include <beluga/tls/tls_extension.hpp>

namespace beluga
{
    class tls_client_hello
    {
    public:
	using random_bytes_type = std::array<std::uint8_t, 28>;
	using cipher_suites_type = std::vector<std::uint16_t>;
	using compression_methods_type = std::vector<std::uint8_t>;
	using extensions_type = std::vector<tls_extension>;
	
	tls_client_hello(std::uint16_t version = 0, std::uint32_t gmt_unix_time = 0, const random_bytes_type& random_bytes = random_bytes_type(), std::uint32_t session_id = 0, const cipher_suites_type& cipher_suites = cipher_suites_type(), const compression_methods_type& compression_methods = compression_methods_type(), const extensions_type& extensions = extensions_type());

	void set_version(std::uint16_t version);
	std::uint16_t get_version() const;
	
	void set_gmt_unix_time(std::uint32_t gmt_unix_time);
	std::uint32_t get_gmt_unix_time() const;

	void set_random_bytes(const random_bytes_type& random_bytes);
	const random_bytes_type& get_random_bytes() const;
	random_bytes_type& get_random_bytes();

	void set_session_id(std::uint32_t session_id);
	std::uint32_t get_session_id() const;

	void set_cipher_suites(cipher_suites_type cipher_suites);
	const cipher_suites_type& get_cipher_suites() const;
	cipher_suites_type& get_cipher_suites();
	
	void set_compression_methods(compression_methods_type compression_methods);
	const compression_methods_type& get_compression_methods() const;
	compression_methods_type& get_compression_methods();

	void set_extensions(extensions_type extensions);
	const extensions_type& get_extensions() const;
	extensions_type& get_extensions();

    private:
	std::uint16_t version;
	
	std::uint32_t gmt_unix_time;
	random_bytes_type random_bytes;
	
	std::uint32_t session_id;
	cipher_suites_type cipher_suites; 	
	compression_methods_type compression_methods;
	extensions_type extensions; 	
    };
}
