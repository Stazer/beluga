# beluga
## Examples
### Basic usage of tcp_server
    boost::asio::io_service io_service;
    auto server = beluga::tcp_server::create(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 8080));
    
	server->on_accept.connect([] (beluga::tcp_server::accept_event& event)
	{
		auto client = beluga::tcp_client::create(event.get_socket());
	});

	server->accept();
	io_service.run();

# Redirect all incomming http requests to 138.201.77.50:80 and print requests header
	boost::asio::io_service io_service;
	auto server = beluga::tcp_server::create(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 8080));
	
	server->on_accept.connect
	    ([] (beluga::tcp_server::accept_event& event)
	     {
		 auto client = beluga::http_client::create(event.get_socket());
		 auto server = beluga::tcp_client::create(client->get_socket().get_io_service());

		 beluga::tcp_tunnel<>::create(client, server);
		 
		 client->on_request.connect
		     ([server] (beluga::http_client::request_event& event)
		      {
			  for(auto i:event.get_request().get_headers())
			      std::cout << i.first << ": " << i.second << std::endl ;
			  
			  server->connect(boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string("138.201.77.50"), 80));
		      });
		 
		 client->receive();
	     });
	
	server->accept();
	io_service.run();
