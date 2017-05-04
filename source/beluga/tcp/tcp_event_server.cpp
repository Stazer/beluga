#include <beluga/tcp/tcp_event_server.hpp>
#include <memory>

beluga::tcp_event_server::tcp_event_server(boost::asio::io_service& io_service, const boost::asio::ip::tcp::endpoint& endpoint):
    acceptor(io_service, endpoint)
{
    accept();
}

boost::asio::ip::tcp::acceptor& beluga::tcp_event_server::get_acceptor()
{
    return acceptor;
}
const boost::asio::ip::tcp::acceptor& beluga::tcp_event_server::get_acceptor() const
{
    return acceptor;
}

void beluga::tcp_event_server::accept()
{
    auto socket = std::make_shared<boost::asio::ip::tcp::socket>(acceptor.get_io_service());
    
    acceptor.async_accept(*socket, [this, socket] (boost::system::error_code error_code)
			  {
			      if(!error_code)
			      {
				  tcp_accept_event event(false, std::move(*socket));
				  on_accept(event);
				  
				  if(!event.get_stop())
				      accept();
			      }
			      else
			      {
				  tcp_accept_error_event event(error_code);
				  on_accept_error(event);
			      }
			  });
}

void beluga::tcp_event_server::on_accept(tcp_accept_event& event)
{
}
void beluga::tcp_event_server::on_accept_error(tcp_accept_error_event& event)
{
}
