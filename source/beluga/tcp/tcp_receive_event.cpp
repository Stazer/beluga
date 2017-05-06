#include <beluga/tcp/tcp_receive_event.hpp>

beluga::tcp_receive_event::tcp_receive_event(bool receive):
    receive(receive)
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
