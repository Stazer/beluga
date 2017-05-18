#pragma once

#include <cstdint>

namespace beluga
{
    class tls_handshake
    {
    public:
	using handshake_type = std::uint8_t;
	
	enum
	{
	    HELLO_REQUEST = 0x00,
	    CLIENT_HELLO = 0x01,
	    SERVER_HELLO = 0x02,
	    CERTIFICATE = 0x0B,
	    SERVER_KEY_EXCHANGE = 0x0C,
	    CERTIFICATE_REQUEST = 0x0D,
	    SERVER_HELLO_DONE = 0x0E,
	    CERTIFICATE_VERIFY = 0x0F,
	    CLIENT_KEY_EXCHANGE = 0x10,
	    FINISHED = 0x14,

	    UNKNOWN,
	};

	using length_type = std::uint32_t;
	
	tls_handshake(handshake_type type = UNKNOWN, length_type length = 0);

	void set_type(handshake_type type);
	handshake_type get_type() const;
	
	void set_length(std::uint32_t length);
        length_type get_length() const;
	
    private: 
	handshake_type type;
        length_type length;
    };
}
