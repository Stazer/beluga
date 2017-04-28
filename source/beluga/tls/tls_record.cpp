#include <beluga/tls/tls_record.hpp>

beluga::tls_record::tls_record(std::uint8_t type, std::uint16_t version, std::uint16_t length):
    type(type),
    version(version),
    length(length)
{
}

void beluga::tls_record::set_type(std::uint8_t type)
{
    this->type = type;
}
std::uint8_t beluga::tls_record::get_type() const
{
    return type;
}

void beluga::tls_record::set_version(std::uint16_t version)
{
    this->version = version;
}
std::uint16_t beluga::tls_record::get_version() const
{
    return version;
}

void beluga::tls_record::set_length(std::uint16_t length)
{
    this->length = length;
}
std::uint16_t beluga::tls_record::get_length() const
{
    return length;
}
