#pragma once

#include <cstdint>
#include <beluga/tls/tls_record_type.hpp>

namespace beluga
{
    class tls_record
    {
    public:
	tls_record(tls_record_type type = tls_record_type::UNKNOWN, std::uint16_t version = 0, std::uint16_t length = 0);
	
	void set_type(tls_record_type type);
	tls_record_type get_type() const;

	void set_version(std::uint16_t version);
	std::uint16_t get_version() const;

	void set_length(std::uint16_t length);
	std::uint16_t get_length() const;
	
    private:
	tls_record_type type;
	std::uint16_t version;
	std::uint16_t length;
    };
}
