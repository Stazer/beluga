#pragma once

#include <boost/asio.hpp>
#include <boost/signals2.hpp>
#include <beluga/event.hpp>
#include <beluga/buffer.hpp>
#include <memory>

namespace beluga
{
    class tcp_client : public std::enable_shared_from_this<tcp_client>
    {
    public:
	class connect_event : public continue_event
	{
	public:
	    connect_event(bool _continue, const boost::asio::ip::tcp::endpoint& endpoint);
	    
	    const boost::asio::ip::tcp::endpoint& get_endpoint() const;	
	    
	private:
	    boost::asio::ip::tcp::endpoint endpoint;
	};

	using connect_error_event = error_event;
	
	class receive_event : public continue_event
	{
	public:
	    receive_event(bool _continue, beluga::dynamic_buffer& buffer);
	    
	    void set_buffer(const beluga::dynamic_buffer& buffer);
	    beluga::dynamic_buffer& get_buffer();
	    const beluga::dynamic_buffer& get_buffer() const;
	    
	private:
	    beluga::dynamic_buffer& buffer;
	};

	using receive_error_event = error_event;

	using on_receive_error_type = boost::signals2::signal<void(receive_error_event& event)>;
	using on_receive_type = boost::signals2::signal<void(receive_event& event)>;
	
	using on_connect_error_type = boost::signals2::signal<void(connect_error_event& event)>;
	using on_connect_type = boost::signals2::signal<void(connect_event& event)>;

	tcp_client(const tcp_client&) = delete;
	tcp_client& operator=(const tcp_client&) = delete;
	
	virtual ~tcp_client() = default;
	
	boost::asio::ip::tcp::socket& get_socket();
	const boost::asio::ip::tcp::socket& get_socket() const;
		
	template <typename... args>
	static std::shared_ptr<tcp_client> create(args&&... params);

	void connect(const boost::asio::ip::tcp::endpoint& endpoint);

	void receive();
	
	on_receive_error_type on_receive_error;
	on_receive_type on_receive;
	
	on_connect_error_type on_connect_error;
	on_connect_type on_connect;

    protected:
	tcp_client(boost::asio::ip::tcp::socket& socket);
	tcp_client(boost::asio::io_service& io_service);

    private:
	boost::asio::ip::tcp::socket socket;
    };
}

#include <beluga/tcp/tcp_client.inl>
