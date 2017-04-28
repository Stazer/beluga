#pragma once

#include <cstdint>

namespace beluga
{
    class tls_handshake
    {
    public:
	tls_handshake(std::uint8_t type = 0, std::uint32_t length = 0);

	void set_type(std::uint8_t type);
	std::uint8_t get_type() const;
	
	void set_length(std::uint32_t length);
	std::uint32_t get_length() const;
	
    private: 
	std::uint8_t type;
	std::uint32_t length;
    };
}
