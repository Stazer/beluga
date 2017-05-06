#pragma once

#include <boost/asio.hpp>
#include <boost/signals2.hpp>
#include <beluga/tcp/tcp_receive_event.hpp>
#include <beluga/tcp/tcp_receive_error_event.hpp>
#include <memory>

namespace beluga
{
    class tcp_client : public std::enable_shared_from_this<tcp_client>
    {
    public:
	using on_receive_signal_type = boost::signals2::signal<void(tcp_receive_event& event)>;
	using on_receive_error_signal_type = boost::signals2::signal<void(tcp_receive_error_event& event)>;

	tcp_client(const tcp_client&) = delete;
	tcp_client& operator=(const tcp_client&) = delete;
	
	virtual ~tcp_client() = default;
	
	boost::asio::ip::tcp::socket& get_socket();
	const boost::asio::ip::tcp::socket& get_socket() const;
		
	static std::shared_ptr<tcp_client> create(boost::asio::ip::tcp::socket socket);
	
	void receive();
	
	virtual void on_receive(tcp_receive_event& event);
	virtual void on_receive_error(tcp_receive_error_event& event);
	
	on_receive_signal_type on_receive_signal;
	on_receive_error_signal_type on_receive_error_signal;

    private:
	tcp_client(boost::asio::ip::tcp::socket socket);

	boost::asio::ip::tcp::socket socket;
    };
}
