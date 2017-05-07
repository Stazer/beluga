#pragma once

#include <boost/asio.hpp>
#include <beluga/event/continue_event.hpp>

namespace beluga
{
    class tcp_connect_event : public continue_event
    {
    public:
	tcp_connect_event(bool _continue, const boost::asio::ip::tcp::endpoint& endpoint);

	void set_endpoint(const boost::asio::ip::tcp::endpoint& endpoint);
	boost::asio::ip::tcp::endpoint& get_endpoint();
	const boost::asio::ip::tcp::endpoint& get_endpoint() const;

    private:
	boost::asio::ip::tcp::endpoint endpoint;
    };
}
