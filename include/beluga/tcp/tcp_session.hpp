#pragma once

#include <boost/asio.hpp>
#include <beluga/buffer.hpp>
#include <memory>
#include <utility>
#include <functional>
#include <iostream>

namespace beluga
{
    class tcp_session : public std::enable_shared_from_this<tcp_session>
    {
    public:
	using on_read_type = std::function<bool(std::size_t)>;
	using on_read_error_type = std::function<void(boost::system::error_code)>;
	using on_write_type = std::function<bool(std::size_t)>;
	using on_write_error_type = std::function<void(boost::system::error_code)>;
	using loop_type = std::function<void()>;
	
	tcp_session(boost::asio::ip::tcp::socket client_socket);
	
	virtual ~tcp_session() = default;
	
	boost::asio::ip::tcp::socket& get_client_socket();
	const boost::asio::ip::tcp::socket& get_client_socket() const;
	
	boost::asio::ip::tcp::socket& get_server_socket();
	const boost::asio::ip::tcp::socket& get_server_socket() const;

	void set_client_buffer(const static_buffer& client_buffer);
	static_buffer& get_client_buffer();
	const static_buffer& get_client_buffer() const;
	
	void set_server_buffer(const static_buffer& server_buffer);
	static_buffer& get_server_buffer();
	const static_buffer& get_server_buffer() const;

	/**
	 * Tunnels incomming traffic of from_socket to to_socket, calling various event functions
	 * Make sure that both sockets are open
	 *
	 * @param from_socket Socket for incomming traffic
	 * @param to_socket Socket for outgoing traffic
	 * @param on_read Function that gets called when traffic was read from from_socket
	 * @param on_on_read_error Function that gets called when an error occured on reading from from_socket
	 * @param on_write Function that gets called when incomming traffic was written to to_socket
	 * @param on_write_error Function that gets called when an error occured on writing to to_socket
	 * @param loop Function that gets called after one tunnel cycle (reading into buffer and writing its content) was executed 
	 */
        void tunnel_socket(boost::asio::ip::tcp::socket& from_socket, boost::asio::ip::tcp::socket& to_socket, on_read_type on_read, on_read_error_type on_read_error, on_write_type on_write, on_write_error_type on_write_error, loop_type, static_buffer& buffer);

        void tunnel_client();
	void tunnel_server();

	virtual void go();	
	
	virtual bool on_client_read(std::size_t length);
	virtual void on_client_read_error(boost::system::error_code error_code);
	virtual bool on_client_write(std::size_t length);
	virtual void on_client_write_error(boost::system::error_code error_code);
	
	virtual bool on_server_read(std::size_t length);
	virtual void on_server_read_error(boost::system::error_code error_code);
	virtual bool on_server_write(std::size_t length);
	virtual void on_server_write_error(boost::system::error_code error_code);
	
    private:
	boost::asio::ip::tcp::socket client_socket;
	boost::asio::ip::tcp::socket server_socket;
	
	static_buffer client_buffer;
	static_buffer server_buffer;
    };
}
