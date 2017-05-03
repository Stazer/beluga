#pragma once

#include <boost/asio.hpp>

namespace beluga
{
    class error_event
    {
    public:
	error_event(boost::system::error_code error_code);
	
	boost::system::error_code get_error_code() const;
	
    private:
	boost::system::error_code error_code;
    };
}
