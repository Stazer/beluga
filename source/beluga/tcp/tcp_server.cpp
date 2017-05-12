#include <beluga/tcp/tcp_server.hpp>

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
	acceptor.async_accept
	    (*socket, [self, socket] (boost::system::error_code error_code)
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

beluga::tcp_server::tcp_server(boost::asio::io_service& io_service, const boost::asio::ip::tcp::endpoint& endpoint):
    acceptor(io_service, endpoint)
{
}
