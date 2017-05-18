#include <beluga/tls/tls_record.hpp>

beluga::tls_record::tls_record(record_type type, version_type version, length_type length):
    type(type),
    version(version),
    length(length)
{
}

void beluga::tls_record::set_type(record_type type)
{
    this->type = type;
}
beluga::tls_record::record_type beluga::tls_record::get_type() const
{
    return type;
}

void beluga::tls_record::set_version(version_type version)
{
    this->version = version;
}
beluga::tls_record::version_type beluga::tls_record::get_version() const
{
    return version;
}

void beluga::tls_record::set_length(length_type length)
{
    this->length = length;
}
beluga::tls_record::length_type beluga::tls_record::get_length() const
{
    return length;
}
