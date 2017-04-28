#pragma once

#include <beluga/tcp/tcp_proxy.hpp>
#include <beluga/tcp/tcp_fixed_session.hpp>

namespace beluga
{
    class tcp_fixed_proxy : public tcp_proxy<tcp_fixed_session>
    {
    public:
	tcp_fixed_proxy(boost::asio::io_service& io_service, const boost::asio::ip::tcp::endpoint& proxy_endpoint, const boost::asio::ip::tcp::endpoint& server_endpoint);

	virtual ~tcp_fixed_proxy() = default;
	
void set_server_endpoint(const boost::asio::ip::tcp::endpoint& server_endpoint);
	const boost::asio::ip::tcp::endpoint& get_server_endpoint() const;

	virtual bool on_accept();

    private:
	boost::asio::ip::tcp::endpoint server_endpoint;
    };
}
