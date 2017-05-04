#pragma once

#include <boost/asio.hpp>

namespace beluga
{
    class tcp_accept_event
    {
    public:
        tcp_accept_event(bool stop, boost::asio::ip::tcp::socket socket);
	
	void set_stop(bool stop);
	bool get_stop() const;
	
	boost::asio::ip::tcp::socket& get_socket();
	const boost::asio::ip::tcp::socket& get_socket() const;
	
    private:
	bool stop;
	boost::asio::ip::tcp::socket socket;
    };
 }
