#include <beluga/tls/tls_extension.hpp>
#include <beluga/buffer/buffer_reader.hpp>

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

std::string beluga::tls_extension::get_server_name() const
{
    beluga::buffer_reader<typename data_type::const_iterator> reader(data.begin(), data.end());

    std::string server_name;

    std::uint16_t list_length = 0;
    std::uint8_t type = 0;
    std::uint16_t length = 0;

    reader >> list_length >> type >> length;

    server_name.resize(length);
    reader.read_byte_array(server_name);

    return server_name;
}

