#pragma once

#include <boost/asio.hpp>
#include <boost/signals2.hpp>
#include <beluga/tcp/tcp_events.hpp>
#include <memory>

namespace beluga
{
    class tcp_client : public std::enable_shared_from_this<tcp_client>
    {
    public:
	using on_pre_receive_type = boost::signals2::signal<void(tcp_pre_receive_event& event)>;
	using on_post_receive_type = boost::signals2::signal<void(tcp_post_receive_event& event)>;
	using on_receive_error_type = boost::signals2::signal<void(tcp_receive_error_event& event)>;

	using on_pre_connect_type = boost::signals2::signal<void(tcp_pre_connect_event& event)>;
	using on_post_connect_type = boost::signals2::signal<void(tcp_post_connect_event& event)>;
	using on_connect_error_type = boost::signals2::signal<void(tcp_connect_error_event& event)>;

	tcp_client(const tcp_client&) = delete;
	tcp_client& operator=(const tcp_client&) = delete;
	
	virtual ~tcp_client() = default;
	
	boost::asio::ip::tcp::socket& get_socket();
	const boost::asio::ip::tcp::socket& get_socket() const;
		
	template <typename... args>
	static std::shared_ptr<tcp_client> create(args&&... params);

	void connect(const boost::asio::ip::tcp::endpoint& endpoint);

	void receive();

	void go();
	
	on_pre_receive_type on_pre_receive;
	on_post_receive_type on_post_receive;
	on_receive_error_type on_receive_error;
	
	on_pre_connect_type on_pre_connect;
	on_post_connect_type on_post_connect;
	on_connect_error_type on_connect_error;

    private:
	tcp_client(boost::asio::ip::tcp::socket& socket);
	tcp_client(boost::asio::io_service& io_service);
	
	boost::asio::ip::tcp::socket socket;
    };
}

#include <beluga/tcp/tcp_client.inl>
