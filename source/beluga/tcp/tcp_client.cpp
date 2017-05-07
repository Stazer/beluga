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

void beluga::tcp_client::connect(const boost::asio::ip::tcp::endpoint& endpoint)
{
    auto self = shared_from_this();
    
    tcp_pre_connect_event event(true, endpoint);
    on_pre_connect(event);
    
    if(event.get_continue())
    {
	get_socket().async_connect(event.get_endpoint(), [self] (boost::system::error_code error_code)
				   {
				       if(!error_code)
				       {
					   tcp_post_connect_event event(true);
					   self->on_post_connect(event);
					   
					   if(event.get_continue())
					       self->receive();
				       }
				   else
				   {
				       tcp_connect_error_event event(error_code);
				       self->on_connect_error(event);
				   }
				   });
    }
}

void beluga::tcp_client::receive()
{
    auto self = shared_from_this();
    auto buffer = std::make_shared<dynamic_buffer>(1024, 0);

    tcp_pre_receive_event event(true, *buffer);
    on_pre_receive(event);

    if(event.get_continue())
    {
	get_socket().async_read_some(boost::asio::buffer(*buffer, buffer->size()),
				     [self, buffer] (boost::system::error_code error_code, std::size_t length)
				     {
					 if(!error_code)
					 {
					     tcp_post_receive_event event(true, *buffer);
					     self->on_post_receive(event);
					     
					     if(event.get_continue())
						 self->receive();
					 }
					 else
					 {
					     tcp_receive_error_event event(error_code);
					     self->on_receive_error(event);
					 }
				     });
    }
}

void beluga::tcp_client::go()
{
    receive();
}

void beluga::tcp_client::on_pre_receive(tcp_pre_receive_event& event)
{
    on_pre_receive_signal(event);
}
void beluga::tcp_client::on_post_receive(tcp_post_receive_event& event)
{
    on_post_receive_signal(event);
}
void beluga::tcp_client::on_receive_error(tcp_receive_error_event& event)
{
    on_receive_error_signal(event);
}

void beluga::tcp_client::on_pre_connect(tcp_pre_connect_event& event)
{
    on_pre_connect_signal(event);
}
void beluga::tcp_client::on_post_connect(tcp_post_connect_event& event)
{
    on_post_connect_signal(event);
}
void beluga::tcp_client::on_connect_error(tcp_connect_error_event& event)
{
    on_connect_error_signal(event);
}

beluga::tcp_client::tcp_client(boost::asio::ip::tcp::socket& socket):
    socket(std::move(socket))
{
}
