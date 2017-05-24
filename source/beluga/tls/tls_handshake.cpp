#include <beluga/tls/tls_handshake.hpp>

beluga::tls_handshake::tls_handshake(handshake_type type, length_type length):
    type(type),
    length(length)
{
}
	
void beluga::tls_handshake::set_type(handshake_type type)
{
    this->type = type;
}
beluga::tls_handshake::handshake_type beluga::tls_handshake::get_type() const
{
    return type;
}

void beluga::tls_handshake::set_length(length_type length)
{
    this->length = length;
}
beluga::tls_handshake::length_type beluga::tls_handshake::get_length() const
{
    return length;
}
