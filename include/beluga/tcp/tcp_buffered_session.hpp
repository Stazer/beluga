#pragma once

#include <beluga/tcp/tcp_session.hpp>

namespace beluga
{
    class tcp_buffered_session : public tcp_session
    {
    public:
	tcp_buffered_session(boost::asio::ip::tcp::socket client_socket);

	virtual ~tcp_buffered_session() = default;

	void set_buffer(const dynamic_buffer& buffer);
	dynamic_buffer& get_buffer();
	const dynamic_buffer& get_buffer() const;

	virtual void go();
	
	virtual bool on_client_read(std::size_t length);
	
    private:
	dynamic_buffer buffer;
    };
}
