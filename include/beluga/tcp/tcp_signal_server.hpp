#pragma once

#include <beluga/tcp/tcp_event_server.hpp>
#include <boost/signals2.hpp>

namespace beluga
{
    class tcp_signal_server : public tcp_event_server
    {
    public:
	using on_accept_signal_type = boost::signals2::signal<void(tcp_accept_event& event)>;
	using on_accept_error_signal_type = boost::signals2::signal<void(tcp_accept_error_event& event)>;

	tcp_signal_server(boost::asio::io_service& io_service, const boost::asio::ip::tcp::endpoint& endpoint);
	
	virtual void on_accept(tcp_accept_event& event);
	virtual void on_accept_error(tcp_accept_error_event& event);
	
	on_accept_signal_type on_accept_signal;
	on_accept_error_signal_type on_accept_error_signal;
    };
}
