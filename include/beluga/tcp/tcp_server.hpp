#pragma once

#include <boost/asio.hpp>
#include <boost/signals2.hpp>
#include <beluga/event.hpp>
#include <memory>

namespace beluga
{
    class tcp_server : public std::enable_shared_from_this<tcp_server>
    {
    public:
	class accept_event : public continue_event 
	{
	public:
	    accept_event(bool _continue, boost::asio::ip::tcp::socket socket);
	    
	    boost::asio::ip::tcp::socket& get_socket();
	    const boost::asio::ip::tcp::socket& get_socket() const;
	    
	private:
	    boost::asio::ip::tcp::socket socket;
	};	

	using accept_error_event = error_event;
	
	using on_accept_error_type = boost::signals2::signal<void(accept_error_event& event)>;
	using on_accept_type = boost::signals2::signal<void(accept_event& event)>;

	tcp_server(const tcp_server&) = delete;
	tcp_server& operator=(const tcp_server&) = delete;

	virtual ~tcp_server() = default;

	template <typename... args>
	static std::shared_ptr<tcp_server> create(args&&... params);
	
	boost::asio::ip::tcp::acceptor& get_acceptor();
	const boost::asio::ip::tcp::acceptor& get_acceptor() const;
	
	void accept();
	
	on_accept_error_type on_accept_error;
	on_accept_type on_accept;

    protected:
	tcp_server(boost::asio::io_service& io_service, const boost::asio::ip::tcp::endpoint& endpoint);
	
    private:
	boost::asio::ip::tcp::acceptor acceptor;
    };
}

#include <beluga/tcp/tcp_server.inl>
