#include <beluga/event/error_event.hpp>

beluga::error_event::error_event(boost::system::error_code error_code):
    error_code(error_code)
{
}

boost::system::error_code beluga::error_event::get_error_code() const
{
    return error_code;
}	


