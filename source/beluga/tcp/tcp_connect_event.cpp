#include <beluga/tcp/tcp_connect_event.hpp>

beluga::tcp_connect_event::tcp_connect_event(bool _continue, const boost::asio::ip::tcp::endpoint& endpoint):
    continue_event(_continue),
    endpoint(endpoint)
{
}

void beluga::tcp_connect_event::set_endpoint(const boost::asio::ip::tcp::endpoint& endpoint)
{
    this->endpoint = endpoint;
}
boost::asio::ip::tcp::endpoint& beluga::tcp_connect_event::get_endpoint()
{
    return endpoint;
}
const boost::asio::ip::tcp::endpoint& beluga::tcp_connect_event::get_endpoint() const
{
    return endpoint;
}


