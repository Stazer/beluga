#include <beluga/tcp/tcp_server.hpp>

beluga::tcp_server::accept_event::accept_event(bool _continue, boost::asio::ip::tcp::socket socket):
    continue_event(_continue),
    socket(std::move(socket))
{
}

boost::asio::ip::tcp::socket& beluga::tcp_server::accept_event::get_socket()
{
    return socket;
}
const boost::asio::ip::tcp::socket& beluga::tcp_server::accept_event::get_socket() const
{
    return socket;
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

    acceptor.async_accept
	(*socket, [self, socket] (boost::system::error_code error_code)
	 {
	     if(!error_code)
	     {
		 accept_event event(true, std::move(*socket));
		 self->on_accept(event);
		 
		 if(event.get_continue())
		     self->accept();
	     }
	     else
	     {
		 accept_error_event event(error_code);
		 self->on_accept_error(event);
	     }
	 });
}

beluga::tcp_server::tcp_server(boost::asio::io_service& io_service, const boost::asio::ip::tcp::endpoint& endpoint):
    acceptor(io_service, endpoint)
{
}
