#pragma once

#include <cstdint>

namespace beluga
{
    class tls_record
    {
    public:
	using record_type = std::uint8_t;

	enum
	{
	    CHANGE_CIPHER_SPEC = 0x14,
	    ALERT = 0x15,
	    HANDSHAKE = 0x16,
	    APPLICATION_DATA = 0x17,
	    HEARTBEAT = 0x18,
		
	    UNKNOWN,
	};

        using version_type = std::uint16_t;
	using length_type = std::uint16_t;
	
	tls_record(record_type type = UNKNOWN, version_type version = 0, length_type length = 0);
	
	void set_type(record_type type);
	record_type get_type() const;

	void set_version(version_type version);
	version_type get_version() const;

	void set_length(length_type length);
	length_type get_length() const;
	
    private:
	record_type type;
	version_type version;
	length_type length;
    };
}
