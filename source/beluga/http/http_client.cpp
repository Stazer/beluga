#include <beluga/http/http_client.hpp>
#include <beluga/http/http_reader.hpp>

beluga::http_client::post_request_event::post_request_event(bool _continue, const http_request& request):
    continue_event(_continue),
    request(request)
{
}

void beluga::http_client::post_request_event::set_request(http_request& request)
{
    this->request = request;
}
beluga::http_request& beluga::http_client::post_request_event::get_request()
{
    return request;
}
const beluga::http_request& beluga::http_client::post_request_event::get_request() const
{
    return request;
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
    auto buffer = std::make_shared<dynamic_buffer>(1024);
    
    this->on_post_receive.connect
	([this, buffer] (tcp_client::post_receive_event& event)
	 {
	     if(on_post_request.empty())
		 return;
		 
	     
	     buffer->insert(buffer->end(), event.get_buffer().begin(), event.get_buffer().end());

	     http_reader<dynamic_buffer::const_iterator> reader(*buffer);
	     http_request request;
	     
	     if(reader.read_request(request))
	     {
		 post_request_event post_request_event(true, request);
		 on_post_request(post_request_event);
		 
		 event.set_continue(post_request_event.get_continue());
	     }
	 });
}
