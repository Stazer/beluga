template <typename... args>
std::shared_ptr<beluga::http_client> beluga::http_client::create(args&&... params)
{
    // TODO std::make_shared
    return std::shared_ptr<http_client>(new http_client(std::forward<args>(params)...));
}
