#include <beluga/http/http_headers.hpp>

beluga::http_headers::http_headers(const map_type& map):
    map(map)
{
}

beluga::http_headers::mapped_type& beluga::http_headers::operator[](const key_type& key)
{
    return map[key];
}
