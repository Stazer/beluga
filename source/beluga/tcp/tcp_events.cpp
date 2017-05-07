#include <beluga/tcp/tcp_events.hpp>

beluga::tcp_post_accept_event::tcp_post_accept_event(bool _continue, boost::asio::ip::tcp::socket socket):
    continue_event(_continue),
    socket(std::move(socket))
{
}

boost::asio::ip::tcp::socket& beluga::tcp_post_accept_event::get_socket()
{
    return socket;
}
const boost::asio::ip::tcp::socket& beluga::tcp_post_accept_event::get_socket() const
{
    return socket;
}

beluga::tcp_pre_connect_event::tcp_pre_connect_event(bool _continue, const boost::asio::ip::tcp::endpoint& endpoint):
    continue_event(_continue),
    endpoint(endpoint)
{
}

void beluga::tcp_pre_connect_event::set_endpoint(const boost::asio::ip::tcp::endpoint& endpoint)
{
    this->endpoint = endpoint;
}
boost::asio::ip::tcp::endpoint& beluga::tcp_pre_connect_event::get_endpoint()
{
    return endpoint;
}
const boost::asio::ip::tcp::endpoint& beluga::tcp_pre_connect_event::get_endpoint() const
{
    return endpoint;
}

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
