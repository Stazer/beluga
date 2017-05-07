#include <boost/asio.hpp>
#include <chrono>
#include <iostream>
#include <string>
#include <cstdint>
#include <memory>
#include <list>
#include <vector>
#include <cassert>
#include <thread>
#include <functional>
#include <typeinfo>
#include <boost/algorithm/string.hpp>
#include <algorithm>

#include <beluga.hpp>

std::ostream& operator <<(std::ostream& stream, const beluga::dynamic_buffer& buffer)
{
    for(auto i:buffer)
	stream << i;
    return stream;
}

std::ostream& operator <<(std::ostream& stream, const beluga::tls_record& record)
{
    stream << static_cast<std::uint16_t>(record.get_type()) << "|" << record.get_version() << "|" << record.get_length();
    return stream;
}

std::ostream& operator <<(std::ostream& stream, const beluga::tls_handshake& handshake)
{
    stream << static_cast<std::uint16_t>(handshake.get_type()) << "|" << handshake.get_length();
    return stream;
}

namespace beluga
{
    template <typename client_type, typename server_type = tcp_client>
    class tcp_tunnel : public std::enable_shared_from_this<tcp_tunnel<client_type, server_type>>
    {
    public:
	using client_pointer = std::shared_ptr<client_type>;
	using server_pointer = std::shared_ptr<server_type>;

	static std::shared_ptr<tcp_tunnel> create(client_pointer client, server_pointer server)
	    {
		return std::shared_ptr<tcp_tunnel>(new tcp_tunnel(client, server));
	    }

	client_pointer& get_client()
	    {
		return client;
	    }
	const client_pointer& get_client() const
	    {
		return client;
	    }
	
	server_pointer& get_server()
	    {
		return client;
	    }
	const server_pointer& get_server() const
	    {
		return client;
	    }

	tcp_tunnel(client_pointer client, server_pointer server):
	    client(client),
	    server(server)
	    {
		auto self = this->shared_from_this();
		auto client_buffer = std::make_shared<dynamic_buffer>(1024);
		
		client->on_receive_signal.connect([self, client_buffer] (beluga::tcp_receive_event& event)
						  {
						      if(!self->get_server()->get_socket().is_open())
							  client_buffer->insert(client_buffer->end(), event.get_buffer().begin(), event.get_buffer().end());
						      else
						      {
							  event.set_continue(false);
						      }
						  });
		
		server->on_receive_signal.connect([self] (beluga::tcp_receive_event& event)
						  {
						      
						  });
						  

						  }

	void go()
	    {
		client->go();
		server->go();
	    }
	    
	
	client_pointer client;
	server_pointer server;
    };
}

int main()
{    
    try
    {
	boost::asio::io_service io_service;
	
	auto server = beluga::tcp_server::create(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 8080));

	server->on_accept_signal.connect([] (beluga::tcp_accept_event& event)
					 {
					     auto client = beluga::tcp_client::create(event.get_socket());
					     
					     client->on_receive_signal.connect([] (beluga::tcp_receive_event& event)
									       {
										   event.set_continue(false);
									       });
					     
					     /*server.on_receive_signal.connect([client], (beluga::tcp_receive_event& event)
					       {
					       event.set_receive(false);
					       client->get_socket().send_async();
					       });*/
					     
					     client->go();
					 });
	
	/*server->on_accept_signal.connect([] (beluga::tcp_accept_event& event)
	  {
	  auto client = beluga::tcp_client::create(event.get_socket());
	  auto buffer = std::make_shared<beluga::dynamic_buffer>();
	  
	  client->on_receive_signal.connect([buffer] (beluga::tcp_receive_event& event)
	  {
	  buffer->insert(buffer->end(), event.get_buffer().begin(), event.get_buffer().end());

										   
									       });
					     
									       client->receive();
									       });*/
	
	server->go();	
	io_service.run();
    }
    catch(std::exception& e)
    {
	std::cout << "Exception: " << e.what();
    }
    
    return 0;
}
