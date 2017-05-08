#include <beluga/tcp/tcp_server.hpp>

/*std::shared_ptr<beluga::tcp_server> beluga::tcp_server::create(boost::asio::io_service& io_service, const boost::asio::ip::tcp::endpoint& endpoint)
{
    // TODO std::make_shared
    return std::shared_ptr<beluga::tcp_server>(new tcp_server(io_service, endpoint));
    }*/

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

    tcp_pre_accept_event event(true);
    on_pre_accept(event);

    if(event.get_continue())
    {
	acceptor.async_accept(*socket, [self, socket] (boost::system::error_code error_code)
			      {
				  if(!error_code)
				  {
				      tcp_post_accept_event event(true, std::move(*socket));
				      self->on_post_accept(event);
				      
				      if(event.get_continue())
					  self->accept();
				  }
				  else
				  {
				      tcp_accept_error_event event(error_code);
				      self->on_accept_error(event);
				  }
			      });
    }
}

void beluga::tcp_server::go()
{
    accept();
}

void beluga::tcp_server::on_pre_accept(tcp_pre_accept_event& event)
{
    on_pre_accept_signal(event);
}
void beluga::tcp_server::on_post_accept(tcp_post_accept_event& event)
{
    on_post_accept_signal(event);
}
void beluga::tcp_server::on_accept_error(tcp_accept_error_event& event)
{
    on_accept_error_signal(event);
}

beluga::tcp_server::tcp_server(boost::asio::io_service& io_service, const boost::asio::ip::tcp::endpoint& endpoint):
    acceptor(io_service, endpoint)
{
}
