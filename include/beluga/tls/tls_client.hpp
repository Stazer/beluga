#pragma once

#include <beluga/tcp/tcp_client.hpp>

namespace beluga
{
    class tls_client : public tcp_client
    {
    public:
	class record_event : public continue_event
	{
	public:
	    record_event(bool _continue, const tls_record record);

	    void set_record(const tls_record& record);
	    tls_record& get_record();
	    const tls_record& get_record() const;
	    
	private:
	    tls_record record;
	};

	class handshake_event : public continue_event
	{
	public:
	    handshake_event(bool _continue, const tls_handshake& handshake);
	    
	    void set_handshake(const tls_handshake& handshake);
	    tls_handshake& get_handshake();
	    const tls_handshake& get_handshake() const;

	private:
	    tls_handshake handshake;
	};
	
	class client_hello_event : public continue_event
	{
	public:
	    client_hello_event(bool _continue, const tls_client_hello& client_hello);
	    
	    void set_client_hello(const tls_client_hello& client_hello);
	    tls_client_hello& get_client_hello();
	    const tls_client_hello& get_client_hello() const;

	private:
	    tls_client_hello client_hello;
	};

	using client_hello_error_event = error_event;
	
	using on_client_hello_error_type = boost::signals2::signal<void(client_hello_error_event& event)>;
	using on_client_hello_type = boost::signals2::signal<void(client_hello_event& event)>;	
	
	virtual ~tls_client() = default;
	
	template <typename... args>
	static std::shared_ptr<http_client> create(args&&... params);
	
	on_client_hello_error_type on_client_hello_error;
        on_client_hello_type on_client_hello;
	
    private:
	http_client(boost::asio::ip::tcp::socket& socket);
	http_client(boost::asio::io_service& io_service);

	void initialize();
    };
}

#include <beluga/tls/tls_client.inl>

