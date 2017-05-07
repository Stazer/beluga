#pragma once

#include <beluga/buffer/dynamic_buffer.hpp>
#include <beluga/event/continue_event.hpp>

namespace beluga
{
    class tcp_receive_event : public continue_event
    {
    public:
	tcp_receive_event(bool _continue, const dynamic_buffer& buffer);

	void set_buffer(const dynamic_buffer& buffer);
        dynamic_buffer& get_buffer();
	const dynamic_buffer& get_buffer() const;
	
    private:
	dynamic_buffer buffer;
    };
}
