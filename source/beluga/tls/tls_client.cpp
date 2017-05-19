#include <beluga/tls/tls_client.hpp>
#include <beluga/tls/tls_reader.hpp>

beluga::tls_client::record_event::record_event(const tls_record& record):
    record(record)
{
}

void beluga::tls_client::record_event::set_record(const tls_record& record)
{
    this->record = record;
}
beluga::tls_record& beluga::tls_client::record_event::get_record()
{
    return record;
}
const beluga::tls_record& beluga::tls_client::record_event::get_record() const
{
    return record;
}

beluga::tls_client::handshake_event::handshake_event(const tls_handshake& handshake):
    handshake(handshake)
{
}

void beluga::tls_client::handshake_event::set_handshake(const tls_handshake& handshake)
{
    this->handshake = handshake;
}
beluga::tls_handshake& beluga::tls_client::handshake_event::get_handshake()
{
    return handshake;
}
const beluga::tls_handshake& beluga::tls_client::handshake_event::get_handshake() const
{
    return handshake;
}

beluga::tls_client::client_hello_event::client_hello_event(const tls_client_hello& client_hello):
    client_hello(client_hello)
{
}

void beluga::tls_client::client_hello_event::set_client_hello(const tls_client_hello& client_hello)
{
    this->client_hello = client_hello;
}
beluga::tls_client_hello& beluga::tls_client::client_hello_event::get_client_hello()
{
    return client_hello;
}
const beluga::tls_client_hello& beluga::tls_client::client_hello_event::get_client_hello() const
{
    return client_hello;
}

beluga::tls_client::tls_client(boost::asio::ip::tcp::socket& socket):
    tcp_client(socket)
{
    initialize();
}
beluga::tls_client::tls_client(boost::asio::io_service& io_service):
    tcp_client(io_service)
{
    initialize();
}

void beluga::tls_client::initialize()
{
    std::shared_ptr<dynamic_buffer> buffer = std::make_shared<dynamic_buffer>();
    
    this->on_receive.connect
	([this, buffer] (tcp_client::receive_event& event)
	 {
	     buffer->insert(buffer->end(), event.get_buffer().begin(), event.get_buffer().end());
	     
	     tls_reader<dynamic_buffer::const_iterator> reader(*buffer);
	     handle_record(reader);
	 });
}

void beluga::tls_client::handle_record(tls_reader<dynamic_buffer::const_iterator>& reader)
{
    tls_record record;

    if(reader.read_record(record))
    {
	record_event event(record);
	on_record(event);
	
	switch(record.get_type())
	{
	case tls_record::HANDSHAKE:
	    handle_handshake(reader);
	    break;
	}
    }
}

void beluga::tls_client::handle_handshake(tls_reader<dynamic_buffer::const_iterator>& reader)
{
    tls_handshake handshake;

    if(reader.read_handshake(handshake))
    {
	handshake_event event(handshake);
	on_handshake(event);

	switch(handshake.get_type())
	{
	case tls_handshake::CLIENT_HELLO:
	    handle_client_hello(reader);
	    break;
	}
    }
}

void beluga::tls_client::handle_client_hello(tls_reader<dynamic_buffer::const_iterator>& reader)
{
    tls_client_hello client_hello;

    if(reader.read_client_hello(client_hello))
    {
	client_hello_event event(client_hello);
	on_client_hello(event);
    }
}
