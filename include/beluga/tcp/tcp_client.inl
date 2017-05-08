template <typename... args>
std::shared_ptr<beluga::tcp_client> beluga::tcp_client::create(args&&... params)
{
    // TODO std::make_shared
    return std::shared_ptr<tcp_client>(new tcp_client(std::forward<args>(params)...));
}
