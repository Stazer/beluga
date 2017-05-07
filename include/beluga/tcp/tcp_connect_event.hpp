#pragma once

#include <boost/asio.hpp>

namespace beluga
{
    class tcp_connect_event
    {
    public:
	tcp_connect_event(const boost::asio::ip::tcp::endpoint& endpoint);

	void set_endpoint(const boost::asio::ip::tcp::endpoint& endpoint);
	boost::asio::ip::tcp::endpoint& get_endpoint();
	const boost::asio::ip::tcp::endpoint& get_endpoint() const;

    private:
	boost::asio::ip::tcp::endpoint endpoint;
    };
}
