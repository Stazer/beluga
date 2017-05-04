#include <beluga/tcp/tcp_accept_event.hpp>

beluga::tcp_accept_event::tcp_accept_event(bool stop, boost::asio::ip::tcp::socket socket):
    stop(stop),
    socket(std::move(socket))
{
}

void beluga::tcp_accept_event::set_stop(bool stop)
{
    this->stop = stop;
}
bool beluga::tcp_accept_event::get_stop() const
{
    return stop;
}

boost::asio::ip::tcp::socket& beluga::tcp_accept_event::get_socket()
{
    return socket;
}
const boost::asio::ip::tcp::socket& beluga::tcp_accept_event::get_socket() const
{
    return socket;
}
