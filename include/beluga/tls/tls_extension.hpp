#pragma once

#include <cstdint>
#include <vector>

namespace beluga
{
    class tls_extension
    {
    public:
	tls_extension(std::uint16_t type = 0, const std::vector<std::uint8_t>& data = std::vector<std::uint8_t>());

	void set_type(std::uint16_t type);
	std::uint16_t get_type() const;

	void set_data(const std::vector<std::uint8_t>& data);
	const std::vector<std::uint8_t>& get_data() const;
	std::vector<std::uint8_t>& get_data();

    private:
	std::uint16_t type;
	std::vector<std::uint8_t> data;
    };
}
