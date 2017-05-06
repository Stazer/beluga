#include <beluga/tcp/tcp_client.hpp>

std::shared_ptr<beluga::tcp_client> beluga::tcp_client::create(boost::asio::ip::tcp::socket& socket)
{
    // TODO std::make_shared
    return std::shared_ptr<tcp_client>(new tcp_client(socket));
}

boost::asio::ip::tcp::socket& beluga::tcp_client::get_socket()
{
    return socket;
}
const boost::asio::ip::tcp::socket& beluga::tcp_client::get_socket() const
{
    return socket;
}

void beluga::tcp_client::receive()
{
    auto self = shared_from_this();
    auto buffer = std::make_shared<dynamic_buffer>(1024, 0);
    
    get_socket().async_read_some(boost::asio::buffer(*buffer, buffer->size()),
				 [self, buffer] (boost::system::error_code error_code, std::size_t length)
				 {
				     if(!error_code)
				     {
					 tcp_receive_event event(true, *buffer);
					 self->on_receive(event);

					 if(event.get_receive())
					     self->receive();
				     }
				     else
				     {
					 tcp_receive_error_event event(error_code);
					 self->on_receive_error(event);
				     }
				 });
}
void beluga::tcp_client::go()
{
    receive();
}

void beluga::tcp_client::on_receive(tcp_receive_event& event)
{
    on_receive_signal(event);
}
void beluga::tcp_client::on_receive_error(tcp_receive_error_event& event)
{
    on_receive_error_signal(event);
}

beluga::tcp_client::tcp_client(boost::asio::ip::tcp::socket& socket):
    socket(std::move(socket))
{
}
