#pragma once

#include <boost/asio.hpp>
#include <boost/signals2.hpp>
#include <beluga/tcp/tcp_accept_event.hpp>
#include <beluga/tcp/tcp_accept_error_event.hpp>
#include <memory>

namespace beluga
{
    class tcp_server : public std::enable_shared_from_this<tcp_server>
    {
    public:
	using on_accept_signal_type = boost::signals2::signal<void(tcp_accept_event& event)>;
	using on_accept_error_signal_type = boost::signals2::signal<void(tcp_accept_error_event& event)>;

	tcp_server(const tcp_server&) = delete;
	tcp_server& operator=(const tcp_server&) = delete;

	virtual ~tcp_server() = default;

	static std::shared_ptr<tcp_server> create(boost::asio::io_service& io_service, const boost::asio::ip::tcp::endpoint& endpoint);

	boost::asio::ip::tcp::acceptor& get_acceptor();
	const boost::asio::ip::tcp::acceptor& get_acceptor() const;
	
	void accept();
	void go();
	
	virtual void on_accept(tcp_accept_event& event);
	virtual void on_accept_error(tcp_accept_error_event& event);
		
	on_accept_signal_type on_accept_signal;
	on_accept_error_signal_type on_accept_error_signal;

    private:
	tcp_server(boost::asio::io_service& io_service, const boost::asio::ip::tcp::endpoint& endpoint);

	boost::asio::ip::tcp::acceptor acceptor;
    };
}
