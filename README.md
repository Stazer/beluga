# beluga
## Usage
### tcp_server
    boost::asio::io_service io_service;
    auto server = beluga::tcp_server::create(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 8080));
    
	server->on_post_accept.connect([] (beluga::tcp_server::post_accept_event& event)
	{
		auto client = beluga::tcp_client::create(event.get_socket());
	});

	server->accept();
	io_service.run();
