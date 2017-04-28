#pragma once

#include <cstdint>
#include <vector>

namespace beluga
{
    class tls_extension
    {
    public:
	using data_type = std::vector<std::uint8_t>;
		
	tls_extension(std::uint16_t type = 0, const data_type& data = data_type());

	void set_type(std::uint16_t type);
	std::uint16_t get_type() const;

	void set_data(const data_type& data);
	const data_type& get_data() const;
        data_type& get_data();

    private:
	std::uint16_t type;
        data_type data;
    };
}
