#pragma once

namespace beluga
{
    class tcp_receive_event
    {
    public:
	tcp_receive_event(bool receive);

	void set_receive(bool receive);
	bool get_receive() const;

    private:
        bool receive;
    };
}
