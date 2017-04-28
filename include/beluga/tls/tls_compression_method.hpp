#pragma once

namespace beluga
{    
    enum TLS_COMPRESSION_METHOD
    {
	TLS_NONE = 0x00,
	TLS_DEFLATE = 0x01,
	TLS_LZS = 0x40,  
    };
}
