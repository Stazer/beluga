#pragma once

#include <boost/asio.hpp>
#include <beluga/event/continue_event.hpp>
#include <beluga/event/error_event.hpp>
#include <beluga/buffer/dynamic_buffer.hpp>

namespace beluga
{
    using tcp_error_event = error_event;
    
    class tcp_post_accept_event : public continue_event
    {
    public:
        tcp_post_accept_event(bool _continue, boost::asio::ip::tcp::socket socket);
	
	boost::asio::ip::tcp::socket& get_socket();
	const boost::asio::ip::tcp::socket& get_socket() const;
	
    private:
	boost::asio::ip::tcp::socket socket;
    };
    
    using tcp_pre_accept_event = continue_event;
    using tcp_accept_error_event = error_event;    

    class tcp_pre_connect_event : public continue_event
    {
    public:
	tcp_pre_connect_event(bool _continue, const boost::asio::ip::tcp::endpoint& endpoint);

	void set_endpoint(const boost::asio::ip::tcp::endpoint& endpoint);
	boost::asio::ip::tcp::endpoint& get_endpoint();	
	const boost::asio::ip::tcp::endpoint& get_endpoint() const;	
	
    private:
	boost::asio::ip::tcp::endpoint endpoint;
    };

    using tcp_post_connect_event = continue_event;
    using tcp_connect_error_event = error_event;
    
    class tcp_receive_event : public continue_event
    {
    public:
	tcp_receive_event(bool _continue, const dynamic_buffer& buffer);
	
	void set_buffer(const dynamic_buffer& buffer);
        dynamic_buffer& get_buffer();
	const dynamic_buffer& get_buffer() const;
	
    private:
	dynamic_buffer buffer;
    };

    using tcp_pre_receive_event = tcp_receive_event;
    using tcp_post_receive_event = tcp_receive_event;
    using tcp_receive_error_event = error_event;
}
