#include <beluga/tls/tls_client.hpp>
#include <beluga/tls/tls_reader.hpp>

beluga::http_client::request_event::request_event(bool _continue):
    continue_event(_continue)
{
}
   
beluga::http_client::http_client(boost::asio::ip::tcp::socket& socket):
    tcp_client(socket)
{
    initialize();
}

beluga::http_client::http_client(boost::asio::io_service& io_service):
    tcp_client(io_service)
{
    initialize();
}

void beluga::http_client::initialize()
{
    std::shared_ptr<dynamic_buffer> buffer = std::make_shared<dynamic_buffer>();
    
    this->on_receive.connect
	([this, buffer] (tcp_client::receive_event& event)
	 {
	     if(on_client_hello.empty())
		 return;

	     buffer->insert(buffer->end(), event.get_buffer().begin(), event.get_buffer().end());
	     
	     tls_reader<dynamic_buffer::const_iterator> reader(*buffer);
	     
	     if(reader.read_request(request))
	     {
		 request_event request_event(true, request);
		 on_request(request_event);
		 
		 event.set_continue(request_event.get_continue());
	     }
	 });
}
