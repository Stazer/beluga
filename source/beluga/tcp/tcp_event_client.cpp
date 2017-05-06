#include <beluga/tcp/tcp_event_client.hpp>
#include <beluga/buffer/static_buffer.hpp>

beluga::tcp_event_client::tcp_event_client(boost::asio::ip::tcp::socket socket):
    socket(std::move(socket))
{
}

boost::asio::ip::tcp::socket& beluga::tcp_event_client::get_socket()
{
    return socket;
}
const boost::asio::ip::tcp::socket& beluga::tcp_event_client::get_socket() const
{
    return socket;
}

void beluga::tcp_event_client::receive()
{
    auto self = shared_from_this();
    auto buffer = std::make_shared<std::vector<std::uint8_t>>();
    buffer->resize(1024, 0);
    
    get_socket().async_read_some(boost::asio::buffer(*buffer, 1024),
				 [self, buffer] (boost::system::error_code error_code, std::size_t length)
				 {
				     if(!error_code)
				     {
					 tcp_receive_event event(true);
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

void beluga::tcp_event_client::on_receive(tcp_receive_event& event)
{
}
void beluga::tcp_event_client::on_receive_error(tcp_receive_error_event& event)
{    
}

/*from_socket.async_read_some(boost::asio::buffer(buffer, beluga::BUFFER_LENGTH),
				[self, &to_socket, on_read, on_read_error, on_write, on_write_error, loop, &buffer] (boost::system::error_code error_code, std::size_t length)
				{	      
				    if(!error_code)
				    {
					if(on_read(length))
					{
					    to_socket.async_write_some(boost::asio::buffer(buffer, length),
								       [self, on_write, on_write_error, loop] (boost::system::error_code error_code, std::size_t length)
								       {
									   if(!error_code)
									   {
									       if(on_write(length))
										   loop();
									   }
									   else
									       on_write_error(error_code);
								       });
					}
				    }
				    else
					on_read_error(error_code);
				});
				}*/
