#include <beluga/tcp/tcp_client.hpp>

beluga::tcp_client::pre_connect_event::pre_connect_event(bool _continue, const boost::asio::ip::tcp::endpoint& endpoint):
    continue_event(_continue),
    endpoint(endpoint)
{
}

void beluga::tcp_client::pre_connect_event::set_endpoint(const boost::asio::ip::tcp::endpoint& endpoint)
{
    this->endpoint = endpoint;
}
boost::asio::ip::tcp::endpoint& beluga::tcp_client::pre_connect_event::get_endpoint()
{
    return endpoint;
}
const boost::asio::ip::tcp::endpoint& beluga::tcp_client::pre_connect_event::get_endpoint() const
{
    return endpoint;
}

beluga::tcp_client::receive_event::receive_event(bool _continue, const dynamic_buffer& buffer):   
    continue_event(_continue),
    buffer(buffer)
{
}

void beluga::tcp_client::receive_event::set_buffer(const dynamic_buffer& buffer)
{
    this->buffer = buffer;
}
beluga::dynamic_buffer& beluga::tcp_client::receive_event::get_buffer()
{
    return buffer;
}
const beluga::dynamic_buffer& beluga::tcp_client::receive_event::get_buffer() const
{
    return buffer;
}

boost::asio::ip::tcp::socket& beluga::tcp_client::get_socket()
{
    return socket;
}
const boost::asio::ip::tcp::socket& beluga::tcp_client::get_socket() const
{
    return socket;
}

void beluga::tcp_client::connect(const boost::asio::ip::tcp::endpoint& endpoint)
{
    auto self = shared_from_this();
    
    pre_connect_event event(true, endpoint);
    on_pre_connect(event);
    
    if(event.get_continue())
    {
	get_socket().async_connect
	    (event.get_endpoint(), [self] (boost::system::error_code error_code)
	     {
		 if(!error_code)
		 {
		     post_connect_event event(true);
		     self->on_post_connect(event);
		     
		     if(event.get_continue())
			 self->receive();
		 }
		 else
		 {
		     connect_error_event event(error_code);
		     self->on_connect_error(event);
		 }
	     });
    }
}

void beluga::tcp_client::receive()
{
    auto self = shared_from_this();
    auto buffer = std::make_shared<dynamic_buffer>(1024, 0);

    pre_receive_event event(true, *buffer);
    on_pre_receive(event);

    if(event.get_continue())
    {
	get_socket().async_read_some
	    (boost::asio::buffer(*buffer, buffer->size()),
	     [self, buffer] (boost::system::error_code error_code, std::size_t length)
	     {
		 if(!error_code)
		 {
		     post_receive_event event(true, *buffer);
		     self->on_post_receive(event);
		     
		     if(event.get_continue())
			 self->receive();
		 }
		 else
		 {
		     receive_error_event event(error_code);
		     self->on_receive_error(event);
		 }
	     });
    }
}

beluga::tcp_client::tcp_client(boost::asio::ip::tcp::socket& socket):
    socket(std::move(socket))
{
}
beluga::tcp_client::tcp_client(boost::asio::io_service& io_service):
    socket(io_service)
{
}
