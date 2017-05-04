#pragma once

#include <boost/asio.hpp>

namespace beluga
{
    class tcp_event_client
    {
	tcp_event_client(boost::asio::ip::tcp::socket socket);

	virtual ~tcp_event_client();
	
	boost::asio::ip::tcp::socket& get_socket();
	const boost::asio::ip::tcp::socket& get_socket() const;

	void receive();
	
	virtual void on_receive(tcp_receive_event& event);
	virtual void on_receive_error(tcp_receive_error_event& event);

    private:
	boost::asio::ip::tcp::socket socket;
    };
}
