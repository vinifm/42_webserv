#ifndef SERVER_HPP
# define SERVER_HPP

#include "includes.hpp"
#include "Listen.hpp"
#include "Location.hpp"
#include "ErrorPages.hpp"

class Server
{
public:
	Server();
	~Server();

	std::vector<std::string>::iterator& initServer(std::vector<std::string>& inputFile,
		std::vector<std::string>::iterator& line);

	Listen		getListen(size_t index) const;
	size_t		getListenSize() const;
	std::string	getServerName(size_t index) const;
	size_t		getServerNameSize() const;
	std::string	getRoot() const;
	std::string	getClientMaxBodySize() const;
	// Location	getLocation(size_t index) const;
	// size_t		getLocationSize() const;

private:
	std::vector<Listen>			_listens;
	std::vector<std::string>	_serverNames;
	std::vector<Location>		_locations;
	std::string					_root;
	std::string					_client_max_body_size;
	ErrorPages					_error_pages;

	std::vector<std::string>::iterator	_line;

	void	_setListen(std::stringstream& values);
	void	_setRoot(std::stringstream& values);
	void	_setServerName(std::stringstream& values);
	void	_setErrorPage(std::stringstream& values);
	void	_setClientSize(std::stringstream& values);
	void	_setLocation(std::vector<std::string>& inputFile, std::string prefix);
};

std::ostream& operator<<(std::ostream& os, const Server& server);

#endif
