#pragma once

#include <boost/asio.hpp>

namespace beluga
{
    class tcp_accept_event
    {
    public:
        tcp_accept_event(bool accept, boost::asio::ip::tcp::socket socket);
	
	void set_accept(bool accept);
	bool get_accept() const;
	
	boost::asio::ip::tcp::socket& get_socket();
	const boost::asio::ip::tcp::socket& get_socket() const;
	
    private:
	bool accept;
	boost::asio::ip::tcp::socket socket;
    };
 }
