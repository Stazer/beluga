#pragma once

#include <cstdint>
#include <vector>

namespace beluga
{
    class tls_extension
    {
    public:
	using extension_type = std::uint16_t;

	enum
	{
	    SERVER_NAME = 0x0000,

	    ELLIPTIC_CURVES = 0x000a,
	    EC_POINT_FORMATS = 0x000b,
	    RENEGOTIATION_INFO = 0xff01,

	    UNKNOWN,
	};
	
	using data_type = std::vector<std::uint8_t>;
		
	tls_extension(extension_type type = UNKNOWN, const data_type& data = data_type());

	void set_type(extension_type type);
	extension_type get_type() const;

	void set_data(const data_type& data);
	const data_type& get_data() const;
        data_type& get_data();

    private:
	extension_type type;
        data_type data;
    };
}
