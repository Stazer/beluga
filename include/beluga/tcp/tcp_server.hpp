#pragma once

#include <boost/asio.hpp>
#include <boost/signals2.hpp>
#include <beluga/tcp/tcp_events.hpp>
#include <memory>

namespace beluga
{
    class tcp_server : public std::enable_shared_from_this<tcp_server>
    {
    public:
	using on_pre_accept_type = boost::signals2::signal<void(tcp_pre_accept_event& event)>;
	using on_post_accept_type = boost::signals2::signal<void(tcp_post_accept_event& event)>;
	using on_accept_error_type = boost::signals2::signal<void(tcp_accept_error_event& event)>;

	tcp_server(const tcp_server&) = delete;
	tcp_server& operator=(const tcp_server&) = delete;

	virtual ~tcp_server() = default;

	template <typename... args>
	static std::shared_ptr<tcp_server> create(args&&... params);
	
	boost::asio::ip::tcp::acceptor& get_acceptor();
	const boost::asio::ip::tcp::acceptor& get_acceptor() const;
	
	void accept();

	void go();
	
	on_pre_accept_type on_pre_accept;
	on_post_accept_type on_post_accept;
	on_accept_error_type on_accept_error;

    private:
	tcp_server(boost::asio::io_service& io_service, const boost::asio::ip::tcp::endpoint& endpoint);

	boost::asio::ip::tcp::acceptor acceptor;
    };
}

#include <beluga/tcp/tcp_server.inl>
