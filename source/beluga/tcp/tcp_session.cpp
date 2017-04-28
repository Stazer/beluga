#include <beluga/tcp/tcp_session.hpp>

beluga::tcp_session::tcp_session(boost::asio::ip::tcp::socket client_socket):
    client_socket(std::move(client_socket)),
    server_socket(client_socket.get_io_service())
{
}

boost::asio::ip::tcp::socket& beluga::tcp_session::get_client_socket()
{
    return client_socket;
}
const boost::asio::ip::tcp::socket& beluga::tcp_session::get_client_socket() const
{
    return client_socket;
}

boost::asio::ip::tcp::socket& beluga::tcp_session::get_server_socket()
{
    return server_socket;
}
const boost::asio::ip::tcp::socket& beluga::tcp_session::get_server_socket() const
{
    return server_socket;
}

void beluga::tcp_session::set_client_buffer(const static_buffer& client_buffer)
{
    std::memcpy(this->client_buffer, client_buffer, BUFFER_LENGTH);
}
beluga::static_buffer& beluga::tcp_session::get_client_buffer()
{
    return client_buffer;
}
const beluga::static_buffer& beluga::tcp_session::get_client_buffer() const
{
    return client_buffer;
}

void beluga::tcp_session::set_server_buffer(const static_buffer& server_buffer)
{
    std::memcpy(this->server_buffer, server_buffer, BUFFER_LENGTH);
}
beluga::static_buffer& beluga::tcp_session::get_server_buffer()
{
    return server_buffer;
}
const beluga::static_buffer& beluga::tcp_session::get_server_buffer() const
{
    return server_buffer;
}

void beluga::tcp_session::tunnel_socket(boost::asio::ip::tcp::socket& from_socket, boost::asio::ip::tcp::socket& to_socket, on_read_type on_read, on_read_error_type on_read_error, on_write_type on_write, on_write_error_type on_write_error, loop_type loop, static_buffer& buffer)
{
    auto self = shared_from_this();
    
    from_socket.async_read_some(boost::asio::buffer(buffer, beluga::BUFFER_LENGTH),
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
}

void beluga::tcp_session::tunnel_client()
{    
    tunnel_socket(client_socket, server_socket,
		  std::bind(&tcp_session::on_client_read, this, std::placeholders::_1),
		  std::bind(&tcp_session::on_client_read_error, this, std::placeholders::_1),
		  std::bind(&tcp_session::on_client_write, this, std::placeholders::_1),
		  std::bind(&tcp_session::on_client_write_error, this, std::placeholders::_1),
		  std::bind(&tcp_session::tunnel_client, this), client_buffer);
}

void beluga::tcp_session::tunnel_server()
{    
    tunnel_socket(server_socket, client_socket,
		  std::bind(&tcp_session::on_server_read, this, std::placeholders::_1),
		  std::bind(&tcp_session::on_server_read_error, this, std::placeholders::_1),
		  std::bind(&tcp_session::on_server_write, this, std::placeholders::_1),
		  std::bind(&tcp_session::on_server_write_error, this, std::placeholders::_1),
		  std::bind(&tcp_session::tunnel_server, this), server_buffer);
}    
    
void beluga::tcp_session::go()
{    
    tunnel_client();
    tunnel_server();
}

bool beluga::tcp_session::on_client_read(std::size_t length)
{
    return true;
}
void beluga::tcp_session::on_client_read_error(boost::system::error_code error_code)
{
}
bool beluga::tcp_session::on_client_write(std::size_t length)
{
    return true;
}
void beluga::tcp_session::on_client_write_error(boost::system::error_code error_code)
{
}

bool beluga::tcp_session::on_server_read(std::size_t length)
{
    return true;
}
void beluga::tcp_session::on_server_read_error(boost::system::error_code error_code)
{
}
bool beluga::tcp_session::on_server_write(std::size_t length)
{
    return true;
}
void beluga::tcp_session::on_server_write_error(boost::system::error_code error_code)
{
}
