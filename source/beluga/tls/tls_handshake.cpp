#include <beluga/tls/tls_handshake.hpp>

beluga::tls_handshake::tls_handshake(std::uint8_t type, std::uint32_t length):
    type(type),
    length(length)
{
}
	
void beluga::tls_handshake::set_type(std::uint8_t type)
{
    this->type = type;
}
std::uint8_t beluga::tls_handshake::get_type() const
{
    return type;
}

void beluga::tls_handshake::set_length(std::uint32_t length)
{
    this->length = length;
}
std::uint32_t beluga::tls_handshake::get_length() const
{
    return length;
}
