#pragma once

#include <beluga/tcp/tcp_client.hpp>
#include <beluga/tls/tls_record.hpp>
#include <beluga/tls/tls_handshake.hpp>
#include <beluga/tls/tls_client_hello.hpp>
#include <beluga/tls/tls_reader.hpp>

namespace beluga
{
    class tls_client : public tcp_client
    {
    public:
	class record_event
	{
	public:
	    record_event(const tls_record& record);
	    
	    void set_record(const tls_record& record);
	    tls_record& get_record();
	    const tls_record& get_record() const;
	    
	private:
	    tls_record record;
	};

	class handshake_event
	{
	public:
	    handshake_event(const tls_handshake& handshake);
	    
	    void set_handshake(const tls_handshake& handshake);
	    tls_handshake& get_handshake();
	    const tls_handshake& get_handshake() const;

	private:
	    tls_handshake handshake;
	};
	
	class client_hello_event
	{
	public:
	    client_hello_event(const tls_client_hello& client_hello);
	    
	    void set_client_hello(const tls_client_hello& client_hello);
	    tls_client_hello& get_client_hello();
	    const tls_client_hello& get_client_hello() const;

	private:
	    tls_client_hello client_hello;
	};
	
	using on_record_type = boost::signals2::signal<void(record_event& event)>;	
	using on_handshake_type = boost::signals2::signal<void(handshake_event& event)>;
	using on_client_hello_type = boost::signals2::signal<void(client_hello_event& event)>;	
	
	virtual ~tls_client() = default;
	
	template <typename... args>
	static std::shared_ptr<tls_client> create(args&&... params);

	on_record_type on_record;
	on_handshake_type on_handshake;
        on_client_hello_type on_client_hello;
	
    private:
	tls_client(boost::asio::ip::tcp::socket& socket);
	tls_client(boost::asio::io_service& io_service);

	void initialize();

	void handle_record(tls_reader<dynamic_buffer::const_iterator>& reader);
	void handle_handshake(tls_reader<dynamic_buffer::const_iterator>& reader);
	void handle_client_hello(tls_reader<dynamic_buffer::const_iterator>& reader);
    };
}

#include <beluga/tls/tls_client.inl>

