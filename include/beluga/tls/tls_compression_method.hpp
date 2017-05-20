#pragma once

#include <cstdint>
#include <type_traits>

namespace beluga
{    
    enum class tls_compression_method : std::uint8_t
    {
	NONE = 0x00,
	DEFLATE = 0x01,
	LZS = 0x40,

	UNKNOWN
    };
}
