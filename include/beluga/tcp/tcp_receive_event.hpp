#pragma once

#include <beluga/buffer/dynamic_buffer.hpp>

namespace beluga
{
    class tcp_receive_event
    {
    public:
	tcp_receive_event(bool receive, const dynamic_buffer& buffer);

	void set_receive(bool receive);
	bool get_receive() const;

	void set_buffer(const dynamic_buffer& buffer);
        dynamic_buffer& get_buffer();
	const dynamic_buffer& get_buffer() const;
	
    private:
        bool receive;
	dynamic_buffer buffer;
    };
}
