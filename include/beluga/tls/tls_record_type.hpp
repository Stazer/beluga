#pragma once

namespace beluga
{
    enum class tls_record_type
    {
	CHANGE_CIPHER_SPEC = 0x14,
	ALERT = 0x15,
	HANDSHAKE = 0x16,
	APPLICATION_DATA = 0x17,
	HEARTBEAT = 0x18,
    };
}
