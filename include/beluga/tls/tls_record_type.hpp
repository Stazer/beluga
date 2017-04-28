#pragma once

namespace beluga
{
    enum TLS_RECORD_TYPE
    {
	TLS_CHANGE_CIPHER_SPEC = 0x14,
	TLS_ALERT = 0x15,
	TLS_HANDSHAKE = 0x16,
	TLS_APPLICATION_DATA = 0x17,
	TLS_HEARTBEAT = 0x18,
    };
}
