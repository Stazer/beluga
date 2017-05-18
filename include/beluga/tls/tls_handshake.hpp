#pragma once

#include <cstdint>
#include <beluga/tls/tls_handshake_type.hpp>

namespace beluga
{
    class tls_handshake
    {
    public:
	tls_handshake(tls_handshake_type type = tls_handshake_type::UNKNOWN, std::uint32_t length = 0);

	void set_type(tls_handshake_type type);
	tls_handshake_type get_type() const;
	
	void set_length(std::uint32_t length);
	std::uint32_t get_length() const;
	
    private: 
	tls_handshake_type type;
	std::uint32_t length;
    };
}
