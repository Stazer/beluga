template <typename local_type, typename remote_type>
template <typename... args>
std::shared_ptr<beluga::tcp_tunnel<local_type, remote_type>> beluga::tcp_tunnel<local_type, remote_type>::create(args&&... params)
{
    auto instance = std::shared_ptr<tcp_tunnel<local_type, remote_type>>(new tcp_tunnel<local_type, remote_type>(std::forward<args>(params)...));
    instance->initialize();
    
    return instance;
}
    
template <typename local_type, typename remote_type>
std::weak_ptr<local_type>& beluga::tcp_tunnel<local_type, remote_type>::get_local()
{
    return local;
}
template <typename local_type, typename remote_type>
const std::weak_ptr<local_type>& beluga::tcp_tunnel<local_type, remote_type>::get_local() const
{
    return local;
}

template <typename local_type, typename remote_type>
std::weak_ptr<remote_type>& beluga::tcp_tunnel<local_type, remote_type>::get_remote()
{
    return remote;
}
template <typename local_type, typename remote_type>
const std::weak_ptr<remote_type>& beluga::tcp_tunnel<local_type, remote_type>::get_remote() const
{
    return remote;
}

template <typename local_type, typename remote_type>
void beluga::tcp_tunnel<local_type, remote_type>::receive()
{
    auto local = get_local().lock();
    auto remote = get_remote().lock();
    
    if(local && remote)
    {
	local->receive();
	remote->receive();
    }
}

template <typename local_type, typename remote_type>
beluga::tcp_tunnel<local_type, remote_type>::tcp_tunnel(std::weak_ptr<local_type> local, std::weak_ptr<remote_type> remote):
    local(local),
    remote(remote)
{
}

template <typename local_type, typename remote_type>
beluga::tcp_tunnel<local_type, remote_type>::tcp_tunnel(std::weak_ptr<local_type> local):
    tcp_tunnel(local, remote_type::create(local->get_socket().get_io_service()))
{
}

template <typename local_type, typename remote_type>
void beluga::tcp_tunnel<local_type, remote_type>::initialize()
{
    auto buffer = std::make_shared<dynamic_buffer>(1024);		
    auto self = this->shared_from_this();
    
    auto local = get_local().lock();
    auto remote = get_remote().lock();
    
    remote->on_post_receive.connect
	([self, buffer] (beluga::tcp_post_receive_event& event)
	 {
	     auto remote = self->get_remote().lock();
	     auto local = self->get_local().lock();
	     
	     if(remote && local)
	     {
		 local->get_socket().async_write_some
		     (boost::asio::buffer(event.get_buffer()), [self] (boost::system::error_code error_code, std::size_t length)
		      {
		      });
	     }
	 });
    
    local->on_post_receive.connect
	([self, buffer] (beluga::tcp_post_receive_event& event)
	 {
	     auto remote = self->get_remote().lock();
	     auto local = self->get_local().lock();
	     
	     if(remote && local)
	     {  
		 if(!remote->get_socket().is_open())
		     buffer->insert(buffer->end(), event.get_buffer().begin(), event.get_buffer().end());
		 else
		 {
		     //event.set_continue(false);
		     
		     remote->get_socket().async_write_some
			 (std::array<boost::asio::const_buffer, 2> {boost::asio::buffer(*buffer), boost::asio::buffer(event.get_buffer())},
			  [self, buffer] (boost::system::error_code error_code, std::size_t bytes_transfered)
			  {
			      if(!error_code)
			      {
				  if(!buffer->empty())
				      buffer->resize(0);
				  
				  //local->receive();
			      }
			      else
			      {
				  tcp_error_event event(error_code);
				  self->on_error(event);
			      }
			  });
		 }
	     }
	 });
}
