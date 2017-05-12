#pragma once

#include <beluga/tcp/tcp_events.hpp>
#include <boost/asio.hpp>
#include <memory>


namespace beluga
{
    template <typename local_type = tcp_client, typename remote_type = tcp_client>
    class tcp_tunnel : public std::enable_shared_from_this<tcp_tunnel<local_type, remote_type>>
    {
    public:
	using on_error_type = boost::signals2::signal<void(tcp_error_event& event)>;

	tcp_tunnel(const tcp_tunnel&) = delete;
	tcp_tunnel& operator=(const tcp_tunnel&) = delete;
	
	template <typename... args>
	static std::shared_ptr<tcp_tunnel<local_type, remote_type>> create(args&&... params);

	std::weak_ptr<local_type>& get_local();
	const std::weak_ptr<local_type>& get_local() const;
	
	std::weak_ptr<remote_type>& get_remote();
	const std::weak_ptr<remote_type>& get_remote() const;
	
	void receive();
	
	on_error_type on_error;

    private:
	tcp_tunnel(std::weak_ptr<local_type> local, std::weak_ptr<remote_type> remote);
	tcp_tunnel(std::weak_ptr<local_type> local);
	
	void initialize();
	    
	std::weak_ptr<local_type> local;
	std::weak_ptr<remote_type> remote;
    };
}

#include <beluga/tcp/tcp_tunnel.inl>
