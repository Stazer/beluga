#include <beluga/tcp/tcp_server.hpp>

std::shared_ptr<beluga::tcp_server> beluga::tcp_server::create(boost::asio::io_service& io_service, const boost::asio::ip::tcp::endpoint& endpoint)
{
    // TODO std::make_shared
    return std::shared_ptr<beluga::tcp_server>(new tcp_server(io_service, endpoint));
}

boost::asio::ip::tcp::acceptor& beluga::tcp_server::get_acceptor()
{
    return acceptor;
}
const boost::asio::ip::tcp::acceptor& beluga::tcp_server::get_acceptor() const
{
    return acceptor;
}

void beluga::tcp_server::accept()
{
    auto self = shared_from_this();
    auto socket = std::make_shared<boost::asio::ip::tcp::socket>(acceptor.get_io_service());
    
    acceptor.async_accept(*socket, [self, socket] (boost::system::error_code error_code)
			  {
			      if(!error_code)
			      {
				  tcp_accept_event event(true, std::move(*socket));
				  self->on_accept(event);
				  
				  if(event.get_accept())
				      self->accept();
			      }
			      else
			      {
				  tcp_accept_error_event event(error_code);
				  self->on_accept_error(event);
			      }
			  });
}

void beluga::tcp_server::on_accept(tcp_accept_event& event)
{
    on_accept_signal(event);
}
void beluga::tcp_server::on_accept_error(tcp_accept_error_event& event)
{
    on_accept_error_signal(event);
}

beluga::tcp_server::tcp_server(boost::asio::io_service& io_service, const boost::asio::ip::tcp::endpoint& endpoint):
    acceptor(io_service, endpoint)
{
}
