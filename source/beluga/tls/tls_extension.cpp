#include <beluga/tls/tls_extension.hpp>

beluga::tls_extension::tls_extension(std::uint16_t type, const std::vector<std::uint8_t>& data):
    type(type),
    data(data)
{
}

void beluga::tls_extension::set_type(std::uint16_t type)
{
    this->type = type;
}
std::uint16_t beluga::tls_extension::get_type() const
{
    return type;
}

void beluga::tls_extension::set_data(const std::vector<std::uint8_t>& data)
{
    this->data = data;
}
const std::vector<std::uint8_t>& beluga::tls_extension::get_data() const
{
    return data;
}
std::vector<std::uint8_t>& beluga::tls_extension::get_data()
{
    return data;
}
