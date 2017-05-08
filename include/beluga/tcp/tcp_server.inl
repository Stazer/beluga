template <typename... args>
std::shared_ptr<beluga::tcp_server> beluga::tcp_server::create(args&&... params)
{
    // TODO std::make_shared
    return std::shared_ptr<tcp_server>(new tcp_server(std::forward<args>(params)...));
}
