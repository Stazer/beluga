#pragma once

#include <cstdint>

namespace beluga
{
    enum class tls_handshake_type : std::uint8_t
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
}
