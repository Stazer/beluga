#include <beluga/http/http_client.hpp>
#include <beluga/http/http_reader.hpp>

beluga::http_client::request_event::request_event(bool _continue, const http_request& request):
    continue_event(_continue),
    request(request)
{
}

void beluga::http_client::request_event::set_request(http_request& request)
{
    this->request = request;
}
beluga::http_request& beluga::http_client::request_event::get_request()
{
    return request;
}
const beluga::http_request& beluga::http_client::request_event::get_request() const
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
    std::shared_ptr<dynamic_buffer> buffer;
    
    this->on_receive.connect
	([this, &buffer] (tcp_client::receive_event& event)
	 {
	     if(on_request.empty())
		 return;

	     if(!buffer)
		 buffer = std::make_shared<dynamic_buffer>(event.get_buffer());
	     else
		 buffer->insert(buffer->end(), event.get_buffer().begin(), event.get_buffer().end());
	     
	     http_reader<dynamic_buffer::const_iterator> reader(*buffer);
	     http_request request;
	     
	     if(reader.read_request(request))
	     {
		 request_event request_event(true, request);
		 on_request(request_event);
		 
		 event.set_continue(request_event.get_continue());
	     }
	 });
}
