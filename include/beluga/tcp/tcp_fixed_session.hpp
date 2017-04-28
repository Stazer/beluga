#pragma once

#include <beluga/tcp/tcp_session.hpp>

namespace beluga
{
    class tcp_fixed_proxy;
    
    class tcp_fixed_session : public tcp_session
    {
    public:
	tcp_fixed_session(boost::asio::ip::tcp::socket client_socket, const boost::asio::ip::tcp::endpoint& server_endpoint = boost::asio::ip::tcp::endpoint());
	
	virtual ~tcp_fixed_session() = default;
	
	void set_server_endpoint(const boost::asio::ip::tcp::endpoint& server_endpoint);
	const boost::asio::ip::tcp::endpoint& get_server_endpoint() const;
	
	virtual void go();

	virtual void on_server_connect();
	virtual void on_server_connect_error(boost::system::error_code error_code);
	
    private:
	boost::asio::ip::tcp::endpoint server_endpoint;
    };
}
