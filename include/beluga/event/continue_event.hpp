#pragma once

namespace beluga
{
    class continue_event
    {
    public:
	continue_event(bool _continue);

	virtual ~continue_event() = default;
	
	void set_continue(bool _continue);
	bool get_continue() const;
	
    private:
	bool _continue;
    };
}
