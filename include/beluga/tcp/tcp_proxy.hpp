#pragma once

#include <boost/asio.hpp>
#include <list>
#include <memory>

namespace beluga
{
    template <typename session_type>
    class tcp_proxy
    {
    public:
	/**
	   Creates a new tcp_proxy object

	   @param io_service Reference to an io service object
	   @param endpoint Address of the listening socket
	*/
	tcp_proxy(boost::asio::io_service& io_service, const boost::asio::ip::tcp::endpoint& endpoint);

	/**
	   Default destructor
	*/
	virtual ~tcp_proxy() = default;

	boost::asio::ip::tcp::socket& get_socket();
	const boost::asio::ip::tcp::socket& get_socket() const;

	boost::asio::ip::tcp::acceptor& get_acceptor();
	const boost::asio::ip::tcp::acceptor& get_acceptor() const;
	
	void accept_connection();
	
	virtual void go();
	
	virtual bool on_accept();
	virtual void on_accept_error(boost::system::error_code error_code);
	
    private:    
	boost::asio::ip::tcp::socket socket;
	boost::asio::ip::tcp::acceptor acceptor;
    };
}

#include <beluga/tcp/tcp_proxy.inl>
