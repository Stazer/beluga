#include <beluga/tcp/tcp_receive_event.hpp>

beluga::tcp_receive_event::tcp_receive_event(bool _continue, const dynamic_buffer& buffer):
    continue_event(_continue),
    buffer(buffer)
{
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
