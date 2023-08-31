#ifndef SERVER_HPP
# define SERVER_HPP

#include "Listen.hpp"
#include "Location.hpp"
#include "ErrorPages.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <map>

class Server
{
public:
	Server();
	~Server();

	void	initServer(std::ifstream& inputFile);

private:
	std::vector<Listen>			_listens;
	std::vector<std::string>	_serverNames;
	std::vector<Location>		_locations;
	// std::string				_root;
	// std::vector<std::string>	_index;
	// bool						_autoindex;
	// std::string				_client_max_body_size;
	// ErrorPages				_error_pages;
	// std::vector<std::string>	_limit_except;
	// std::string				_redirect;

	void	_setListen(std::stringstream& values);
	void	_setRoot();
	void	_setServerName();
	void	_setErrorPage();
	void	_setClientSize();
	void	_setLocation();
};

#endif
