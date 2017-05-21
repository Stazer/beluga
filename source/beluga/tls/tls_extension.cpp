#include <beluga/tls/tls_extension.hpp>

beluga::tls_extension::tls_extension(beluga::tls_extension::extension_type type, const data_type& data):
    type(type),
    data(data)
{
}

void beluga::tls_extension::set_type(beluga::tls_extension::extension_type type)
{
    this->type = type;
}
beluga::tls_extension::extension_type beluga::tls_extension::get_type() const
{
    return type;
}

void beluga::tls_extension::set_data(const data_type& data)
{
    this->data = data;
}
const beluga::tls_extension::data_type& beluga::tls_extension::get_data() const
{
    return data;
}
beluga::tls_extension::data_type& beluga::tls_extension::get_data()
{
    return data;
}
