template <typename... args>
std::shared_ptr<beluga::tls_client> beluga::tls_client::create(args&&... params)
{
    // TODO std::make_shared
    return std::shared_ptr<tls_client>(new tls_client(std::forward<args>(params)...));
}
