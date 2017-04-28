#pragma once

#include <cstdint>

namespace beluga
{
    class tls_record
    {
    public:
	tls_record(std::uint8_t type = 0, std::uint16_t version = 0, std::uint16_t length = 0);
	
	void set_type(std::uint8_t type);
	std::uint8_t get_type() const;

	void set_version(std::uint16_t version);
	std::uint16_t get_version() const;

	void set_length(std::uint16_t length);
	std::uint16_t get_length() const;
	
    private:
	std::uint8_t type;
	std::uint16_t version;
	std::uint16_t length;
    };
}
