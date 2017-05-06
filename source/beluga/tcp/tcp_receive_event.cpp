#include <beluga/tcp/tcp_receive_event.hpp>

beluga::tcp_receive_event::tcp_receive_event(bool receive, const dynamic_buffer& buffer):
    receive(receive),
    buffer(buffer)
{
}

void beluga::tcp_receive_event::set_receive(bool receive)
{
    this->receive = receive;
}
bool beluga::tcp_receive_event::get_receive() const
{
    return receive;
}

void beluga::tcp_receive_event::set_buffer(const dynamic_buffer& buffer)
{
    this->buffer = buffer;
}
beluga::dynamic_buffer& beluga::tcp_receive_event::get_buffer()
{
    return buffer;
}
const beluga::dynamic_buffer& beluga::tcp_receive_event::get_buffer() const
{
    return buffer;
}
