#include <beluga/tcp/tcp_signal_server.hpp>

beluga::tcp_signal_server::tcp_signal_server(boost::asio::io_service& io_service, const boost::asio::ip::tcp::endpoint& endpoint):
    tcp_event_server(io_service, endpoint)
{
}

void beluga::tcp_signal_server::on_accept(tcp_accept_event& event)
{
    on_accept_signal(event);
}
void beluga::tcp_signal_server::on_accept_error(tcp_accept_error_event& event)
{
    on_accept_error_signal(event);
}

