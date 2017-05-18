#include <beluga/tls/tls_record.hpp>

beluga::tls_record::tls_record(tls_record_type type, std::uint16_t version, std::uint16_t length):
    type(type),
    version(version),
    length(length)
{
}

void beluga::tls_record::set_type(tls_record_type type)
{
    this->type = type;
}
beluga::tls_record_type beluga::tls_record::get_type() const
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
