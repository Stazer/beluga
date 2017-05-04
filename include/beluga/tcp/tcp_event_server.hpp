#pragma once

#include <boost/asio.hpp>
#include <beluga/tcp/tcp_accept_event.hpp>
#include <beluga/tcp/tcp_accept_error_event.hpp>

namespace beluga
{
    class tcp_event_server
    {
    public:
	tcp_event_server(boost::asio::io_service& io_service, const boost::asio::ip::tcp::endpoint& endpoint);

	virtual ~tcp_event_server() = default;

	boost::asio::ip::tcp::acceptor& get_acceptor();
	const boost::asio::ip::tcp::acceptor& get_acceptor() const;
	
	void accept();
	
	virtual void on_accept(tcp_accept_event& event);
	virtual void on_accept_error(tcp_accept_error_event& event);
	
    private:    
	boost::asio::ip::tcp::acceptor acceptor;
    };
}
