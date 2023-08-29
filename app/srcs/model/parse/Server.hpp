#ifndef SERVER_HPP
# define SERVER_HPP

#include "Listen.hpp"
#include "Location.hpp"
#include "ErrorPages.hpp"

class Server
{
public:
	Server();
	~Server();

private:
	std::vector<Listen>			_listens;
	std::vector<std::string>	_server_names;
	std::vector<Location>		_locations;
	std::string					_root;
	std::vector<std::string>	_index;
	bool						_autoindex;
	std::string					_client_max_body_size;
	ErrorPages					_error_pages;
	std::vector<std::string>	_limit_except;
	std::string					_redirect;
};

#endif
