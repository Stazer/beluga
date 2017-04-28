#pragma once

#include <cstdint>

namespace beluga
{
    enum
    {
	BUFFER_LENGTH = 1024
    };
    
    using static_buffer = std::uint8_t[BUFFER_LENGTH];
}
