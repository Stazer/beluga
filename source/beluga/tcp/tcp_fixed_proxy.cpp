#include <beluga/tcp/tcp_fixed_proxy.hpp>

beluga::tcp_fixed_proxy::tcp_fixed_proxy(boost::asio::io_service& io_service, const boost::asio::ip::tcp::endpoint& proxy_endpoint, const boost::asio::ip::tcp::endpoint& server_endpoint):
    tcp_proxy(io_service, proxy_endpoint),
    server_endpoint(server_endpoint)
{
}

void beluga::tcp_fixed_proxy::set_server_endpoint(const boost::asio::ip::tcp::endpoint& server_endpoint)
{
    this->server_endpoint = server_endpoint;
}
const boost::asio::ip::tcp::endpoint& beluga::tcp_fixed_proxy::get_server_endpoint() const
{
    return server_endpoint;
}

bool beluga::tcp_fixed_proxy::on_accept()
{
    std::make_shared<tcp_fixed_session>(std::move(get_socket()), server_endpoint)->go();

    return true;
}
