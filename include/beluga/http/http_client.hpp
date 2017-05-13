#pragma once

#include <beluga/tcp/tcp_client.hpp>
#include <beluga/http/http_request.hpp>

namespace beluga
{
    class http_client : public tcp_client
    {
    public:
	class post_request_event : public continue_event
	{
	public:
	    post_request_event(bool _continue, const http_request& request);
	    
	    void set_request(http_request& request);
	    http_request& get_request();
	    const http_request& get_request() const;
	    
	private:
	    http_request request;
	};

	using request_error_event = error_event;
	using pre_request_event = continue_event;
	
	using on_request_error_type = boost::signals2::signal<void(request_error_event& event)>;
	using on_pre_request_type = boost::signals2::signal<void(pre_request_event& event)>;	
	using on_post_request_type = boost::signals2::signal<void(post_request_event& event)>;	
	
	virtual ~http_client() = default;
	
	template <typename... args>
	static std::shared_ptr<http_client> create(args&&... params);
	
	on_request_error_type on_request_error;
        on_pre_request_type on_pre_request;
        on_post_request_type on_post_request;
	
    private:
	http_client(boost::asio::ip::tcp::socket& socket);
	http_client(boost::asio::io_service& io_service);

	void initialize();
    };
}

#include <beluga/http/http_client.inl>
