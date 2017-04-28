#include <beluga/tcp/tcp_fixed_session.hpp>
#include <beluga/tcp/tcp_fixed_proxy.hpp>

beluga::tcp_fixed_session::tcp_fixed_session(boost::asio::ip::tcp::socket client_socket, const boost::asio::ip::tcp::endpoint& server_endpoint):
    tcp_session(std::move(client_socket)),
    server_endpoint(server_endpoint)
{
}

void beluga::tcp_fixed_session::set_server_endpoint(const boost::asio::ip::tcp::endpoint& server_endpoint)
{
    this->server_endpoint = server_endpoint;
}
const boost::asio::ip::tcp::endpoint& beluga::tcp_fixed_session::get_server_endpoint() const
{
    return server_endpoint;
}

void beluga::tcp_fixed_session::go()
{
    auto self = shared_from_this();
    
    get_server_socket().async_connect(server_endpoint, [this, self] (boost::system::error_code error_code)
				      {
					  if(!error_code)
					      on_server_connect();
					  else
					      on_server_connect_error(error_code);
				      });
}

void beluga::tcp_fixed_session::on_server_connect()
{
    tcp_session::go();
}
void beluga::tcp_fixed_session::on_server_connect_error(boost::system::error_code error_code)
{
}
