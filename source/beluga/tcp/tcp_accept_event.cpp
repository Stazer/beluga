#include <beluga/tcp/tcp_accept_event.hpp>

beluga::tcp_accept_event::tcp_accept_event(bool accept, boost::asio::ip::tcp::socket socket):
    accept(accept),
    socket(std::move(socket))
{
}

void beluga::tcp_accept_event::set_accept(bool accept)
{
    this->accept = accept;
}
bool beluga::tcp_accept_event::get_accept() const
{
    return accept;
}

boost::asio::ip::tcp::socket& beluga::tcp_accept_event::get_socket()
{
    return socket;
}
const boost::asio::ip::tcp::socket& beluga::tcp_accept_event::get_socket() const
{
    return socket;
}
