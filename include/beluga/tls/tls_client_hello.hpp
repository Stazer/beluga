#pragma once

#include <cstdint>
#include <array>
#include <vector>
#include <beluga/tls/tls_compression_method.hpp>
#include <beluga/tls/tls_cipher_suite.hpp>
#include <beluga/tls/tls_extension.hpp>

namespace beluga
{
    class tls_client_hello
    {
    public:
	using version_type = std::uint16_t;
	using gmt_unix_time_type = std::uint32_t;
	using random_bytes_type = std::array<std::uint8_t, 28>;
	using session_id_type = std::uint64_t;
	using cipher_suites_type = std::vector<tls_cipher_suite>;
	using compression_methods_type = std::vector<tls_compression_method>;
	using extensions_type = std::vector<tls_extension>;
	
	tls_client_hello(version_type version = 0, gmt_unix_time_type gmt_unix_time = 0, const random_bytes_type& random_bytes = random_bytes_type(), session_id_type session_id = 0, const cipher_suites_type& cipher_suites = cipher_suites_type(), const compression_methods_type& compression_methods = compression_methods_type(), const extensions_type& extensions = extensions_type());

	void set_version(version_type version);
	version_type get_version() const;
	
	void set_gmt_unix_time(gmt_unix_time_type gmt_unix_time);
	gmt_unix_time_type get_gmt_unix_time() const;

	void set_random_bytes(const random_bytes_type& random_bytes);
	const random_bytes_type& get_random_bytes() const;
	random_bytes_type& get_random_bytes();

	void set_session_id(session_id_type session_id);
	session_id_type get_session_id() const;

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
	version_type version;
	
	gmt_unix_time_type gmt_unix_time;
	random_bytes_type random_bytes;
	
	session_id_type session_id;
	cipher_suites_type cipher_suites; 	
	compression_methods_type compression_methods;
	extensions_type extensions; 	
    };
}
