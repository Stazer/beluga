template <typename iterator_type>
template <typename container_type>
beluga::http_reader<iterator_type>::http_reader(const container_type& container):
    protocol_reader<iterator_type>(container)
{
}
template <typename iterator_type>
beluga::http_reader<iterator_type>::http_reader(iterator_type from, iterator_type to):
    protocol_reader<iterator_type>(from, to)
{
}

#include <iostream>

template <typename iterator_type>
bool beluga::http_reader<iterator_type>::read_request(http_request& request)
{    
    http_method method = http_method::UNKNOWN;
    std::string uri = "";
    http_version version = http_version::UNKNOWN;
    http_headers headers;
   
    if(!read_request_line(method, uri, version) || !read_headers(headers))
	return false;
    
    request.set_method(method);
    request.set_uri(uri);
    request.set_version(version);
    request.set_headers(headers);
    
    return true;
}

template <typename iterator_type>
bool beluga::http_reader<iterator_type>::read_request_line(http_method& method, std::string& uri, http_version& version)
{
    const std::string delimiter = "\r\n";
    auto iterator = std::search(this->get_reader().get_iterator(), this->get_to(), delimiter.begin(), delimiter.end());    

    if(iterator == this->get_to())
	return false;
    
    std::string content = std::string(this->get_reader().get_iterator(), iterator);
    std::vector<std::string> request_line_parts;
    boost::algorithm::split(request_line_parts, content, boost::is_any_of(" "), boost::token_compress_on);

    if(request_line_parts.size() != 3)
	return false;
    
    method = to_http_method(request_line_parts[0]);
    uri = request_line_parts[1];
    version = to_http_version(request_line_parts[2]);
	
    this->get_reader().set_iterator(iterator + delimiter.length());
    
    return true;
}

template <typename iterator_type>
bool beluga::http_reader<iterator_type>::read_headers(http_headers& headers)
{
    const std::string delimiter = "\r\n\r\n";    
    auto iterator = std::search(this->get_reader().get_iterator(), this->get_to(), delimiter.begin(), delimiter.end());   

    if(iterator == this->get_to())
	return false;

    std::string content = std::string(this->get_reader().get_iterator(), iterator);
    std::vector<std::string> headers_parts;
    boost::algorithm::split(headers_parts, content, boost::is_any_of("\r\n"), boost::token_compress_on);
    
    for(auto header: headers_parts)
    {
	std::vector<std::string> header_parts;
	boost::algorithm::split(header_parts, header, boost::is_any_of(":"), boost::token_compress_on);
	
	if(header_parts.size() > 0)
	{
	    std::string value = "";

	    for(auto iterator = header_parts.begin() + 1; iterator != header_parts.end(); ++iterator)
	    {
		if(iterator != header_parts.begin() + 1)
		    value += ":";
		
		value += *iterator;
	    }

	    boost::algorithm::trim(header_parts[0]);
	    boost::algorithm::trim(value);

	    // TODO Capitalize each "word" in header key
	    headers[header_parts[0]] = value;
	}
    }

    this->get_reader().set_iterator(iterator + delimiter.length());
    
    return true;
}
