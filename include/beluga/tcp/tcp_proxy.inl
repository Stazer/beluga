template <typename session_type>
beluga::tcp_proxy<session_type>::tcp_proxy(boost::asio::io_service& io_service, const boost::asio::ip::tcp::endpoint& endpoint):
    socket(io_service),
    acceptor(io_service, endpoint)
{
}

template <typename session_type>
boost::asio::ip::tcp::acceptor& beluga::tcp_proxy<session_type>::get_acceptor()
{
    return acceptor;
}
template <typename session_type>
const boost::asio::ip::tcp::acceptor& beluga::tcp_proxy<session_type>::get_acceptor() const
{
    return acceptor;
}

template <typename session_type>
boost::asio::ip::tcp::socket& beluga::tcp_proxy<session_type>::get_socket()
{
    return socket;
}
template <typename session_type>
const boost::asio::ip::tcp::socket& beluga::tcp_proxy<session_type>::get_socket() const
{
    return socket;
}

template <typename session_type>
void beluga::tcp_proxy<session_type>::accept_connection()
{
    acceptor.async_accept(socket, [this] (boost::system::error_code error_code)
			  {
			      if(!error_code)
			      {
				  if(on_accept())
				      accept_connection();
			      }
			      else
				  on_accept_error(error_code);
			  });
}

template <typename session_type>
void beluga::tcp_proxy<session_type>::go()
{
    accept_connection();
}

template <typename session_type>
bool beluga::tcp_proxy<session_type>::on_accept()
{
    std::make_shared<session_type>(std::move(socket))->go();

    return true;
}
template <typename session_type>
void beluga::tcp_proxy<session_type>::on_accept_error(boost::system::error_code error_code)
{
}
