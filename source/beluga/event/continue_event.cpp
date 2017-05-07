#include <beluga/event/continue_event.hpp>

beluga::continue_event::continue_event(bool _continue):
    _continue(_continue)
{
}

void beluga::continue_event::set_continue(bool _continue)
{
    this->_continue = _continue;
}
bool beluga::continue_event::get_continue() const
{
    return _continue;
}
