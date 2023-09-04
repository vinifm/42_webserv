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

	void		printAllListen() const;
	Listen		getListen(size_t index) const;
	size_t		getListenSize() const;
	void		printAllServerNames() const;
	std::string	getServerName(size_t index) const;
	size_t		getServerNameSize() const;
	void		printAllLocation() const;
	Location	getLocation(size_t index) const;
	size_t		getLocationSize() const;
	void		printAllIndex() const;
	std::string	getIndex(size_t index) const;
	size_t		getIndexSize() const;

private:
	std::vector<Listen>			_listens;
	std::vector<std::string>	_serverNames;
	std::vector<Location>		_locations;
	std::vector<std::string>	_index;
	// std::string				_root;
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
	void	_setLocation(std::ifstream& inputFile, std::string prefix);
};

std::ostream& operator<<(std::ostream& os, const Server& server);

#endif
