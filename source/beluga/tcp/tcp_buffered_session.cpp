#include <beluga/tcp/tcp_buffered_session.hpp>

beluga::tcp_buffered_session::tcp_buffered_session(boost::asio::ip::tcp::socket client_socket):
    tcp_session(std::move(client_socket))
{
}

void beluga::tcp_buffered_session::set_buffer(const dynamic_buffer& buffer)
{
    this->buffer = buffer;
}
beluga::dynamic_buffer& beluga::tcp_buffered_session::get_buffer()
{
    return buffer;
}
const beluga::dynamic_buffer& beluga::tcp_buffered_session::get_buffer() const
{
    return buffer;
}

void beluga::tcp_buffered_session::go()
{
    tunnel_client();
}

bool beluga::tcp_buffered_session::on_client_read(std::size_t length)
{
    if(!tcp_session::on_client_read(length))
	return false;
    
    if(!get_server_socket().is_open())
	buffer.insert(buffer.end(), get_client_buffer(), get_client_buffer() + length);

    tunnel_client();
    
    return false;
}
