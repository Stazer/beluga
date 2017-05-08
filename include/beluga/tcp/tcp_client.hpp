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
	using on_pre_receive_signal_type = boost::signals2::signal<void(tcp_pre_receive_event& event)>;
	using on_post_receive_signal_type = boost::signals2::signal<void(tcp_post_receive_event& event)>;
	using on_receive_error_signal_type = boost::signals2::signal<void(tcp_receive_error_event& event)>;

	using on_pre_connect_signal_type = boost::signals2::signal<void(tcp_pre_connect_event& event)>;
	using on_post_connect_signal_type = boost::signals2::signal<void(tcp_post_connect_event& event)>;
	using on_connect_error_signal_type = boost::signals2::signal<void(tcp_connect_error_event& event)>;

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
	
	virtual void on_pre_receive(tcp_pre_receive_event& event);
	virtual void on_post_receive(tcp_post_receive_event& event);
	virtual void on_receive_error(tcp_receive_error_event& event);
	
	virtual void on_pre_connect(tcp_pre_connect_event& event);
	virtual void on_post_connect(tcp_post_connect_event& event);
	virtual void on_connect_error(tcp_connect_error_event& event);
	
	on_pre_receive_signal_type on_pre_receive_signal;
	on_post_receive_signal_type on_post_receive_signal;
	on_receive_error_signal_type on_receive_error_signal;
	
	on_pre_connect_signal_type on_pre_connect_signal;
	on_post_connect_signal_type on_post_connect_signal;
	on_connect_error_signal_type on_connect_error_signal;

    private:
	tcp_client(boost::asio::ip::tcp::socket& socket);

	boost::asio::ip::tcp::socket socket;
    };
}

#include <beluga/tcp/tcp_client.inl>
