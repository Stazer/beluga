#include <beluga/http/http_headers.hpp>

beluga::http_headers::http_headers(const map_type& map):
    map(map)
{
}

beluga::http_headers::mapped_type& beluga::http_headers::operator[](const key_type& key)
{
    return map[key];
}

beluga::http_headers::iterator beluga::http_headers::begin()
{
    return map.begin();
}
beluga::http_headers::const_iterator beluga::http_headers::begin() const
{
    return map.begin();
}
beluga::http_headers::const_iterator beluga::http_headers::cbegin() const
{
    return map.cbegin();
}

beluga::http_headers::iterator beluga::http_headers::end()
{
    return map.end();
}
beluga::http_headers::const_iterator beluga::http_headers::end() const
{
    return map.end();
}
beluga::http_headers::const_iterator beluga::http_headers::cend() const
{
    return map.cend();
}
