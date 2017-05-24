#include <beluga/tls/tls_client_hello.hpp>

beluga::tls_client_hello::tls_client_hello(version_type version, gmt_unix_time_type gmt_unix_time, const random_bytes_type& random_bytes, session_id_type session_id, const cipher_suites_type& cipher_suites, const compression_methods_type& compression_methods, const extensions_type& extensions):
    version(version),
    gmt_unix_time(gmt_unix_time),
    random_bytes(random_bytes),
    session_id(session_id),
    cipher_suites(cipher_suites),
    compression_methods(compression_methods),
    extensions(extensions)
{
}

void beluga::tls_client_hello::set_version(version_type version)
{
    this->version = version;
}
beluga::tls_client_hello::version_type beluga::tls_client_hello::get_version() const
{
    return version;
}

void beluga::tls_client_hello::set_gmt_unix_time(gmt_unix_time_type gmt_unix_time)
{
    this->gmt_unix_time = gmt_unix_time;
}
beluga::tls_client_hello::gmt_unix_time_type beluga::tls_client_hello::get_gmt_unix_time() const
{
    return gmt_unix_time;
}

void beluga::tls_client_hello::set_random_bytes(const random_bytes_type& random_bytes)
{
    this->random_bytes = random_bytes;
}
const beluga::tls_client_hello::random_bytes_type& beluga::tls_client_hello::get_random_bytes() const
{
    return random_bytes;
}
beluga::tls_client_hello::random_bytes_type& beluga::tls_client_hello::get_random_bytes()
{
    return random_bytes;
}

void beluga::tls_client_hello::set_session_id(session_id_type session_id)
{
    this->session_id = session_id;
}
beluga::tls_client_hello::session_id_type beluga::tls_client_hello::get_session_id() const
{
    return session_id;
}

void beluga::tls_client_hello::set_cipher_suites(cipher_suites_type cipher_suites)
{
    this->cipher_suites = cipher_suites;
}
const beluga::tls_client_hello::cipher_suites_type& beluga::tls_client_hello::get_cipher_suites() const
{
    return cipher_suites;
}
beluga::tls_client_hello::cipher_suites_type& beluga::tls_client_hello::get_cipher_suites()
{
    return cipher_suites;
}

void beluga::tls_client_hello::set_compression_methods(compression_methods_type compression_methods)
{
    this->compression_methods = compression_methods;
}
const beluga::tls_client_hello::compression_methods_type& beluga::tls_client_hello::get_compression_methods() const
{
    return compression_methods;
}
beluga::tls_client_hello::compression_methods_type& beluga::tls_client_hello::get_compression_methods()
{
    return compression_methods;
}

void beluga::tls_client_hello::set_extensions(extensions_type extensions)
{
    this->extensions = extensions;
}
const beluga::tls_client_hello::extensions_type& beluga::tls_client_hello::get_extensions() const
{
    return extensions;
}
beluga::tls_client_hello::extensions_type& beluga::tls_client_hello::get_extensions()
{
    return extensions;
}
