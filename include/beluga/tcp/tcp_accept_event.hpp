#pragma once

#include <boost/asio.hpp>
#include <beluga/event/continue_event.hpp>

namespace beluga
{
    class tcp_accept_event : public continue_event
    {
    public:
        tcp_accept_event(bool _continue, boost::asio::ip::tcp::socket socket);

	boost::asio::ip::tcp::socket& get_socket();
	const boost::asio::ip::tcp::socket& get_socket() const;
	
    private:
	boost::asio::ip::tcp::socket socket;
    };
 }
