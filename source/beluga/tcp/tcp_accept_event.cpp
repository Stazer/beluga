#include <beluga/tcp/tcp_accept_event.hpp>

beluga::tcp_accept_event::tcp_accept_event(bool _continue, boost::asio::ip::tcp::socket socket):
    continue_event(_continue),
    socket(std::move(socket))
{
}

boost::asio::ip::tcp::socket& beluga::tcp_accept_event::get_socket()
{
    return socket;
}
const boost::asio::ip::tcp::socket& beluga::tcp_accept_event::get_socket() const
{
    return socket;
}
