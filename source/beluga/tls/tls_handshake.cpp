#include <beluga/tls/tls_handshake.hpp>

beluga::tls_handshake::tls_handshake(tls_handshake_type type, std::uint32_t length):
    type(type),
    length(length)
{
}
	
void beluga::tls_handshake::set_type(tls_handshake_type type)
{
    this->type = type;
}
beluga::tls_handshake_type beluga::tls_handshake::get_type() const
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
