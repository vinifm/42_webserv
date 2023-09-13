#ifndef SERVER_HPP
# define SERVER_HPP

#include <includes.hpp>
#include <Listen.hpp>
#include <Location.hpp>
#include <ErrorPages.hpp>

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
	ErrorPages	getErrorPages() const;
	Location	getLocation(size_t index) const;
	size_t		getLocationSize() const;
	std::vector<Location> getLocations() const;
	std::string	getIndex(size_t index) const;
	std::vector<std::string>	getIndex() const;
	size_t		getIndexSize() const;
	bool		getAutoindex() const;

private:
	std::vector<Location>		_locations;
	std::vector<Listen>			_listens;
	std::vector<std::string>	_serverNames;
	std::string					_root;
	std::string					_client_max_body_size;
	ErrorPages					_error_pages;
	std::vector<std::string>	_index;
	bool						_autoindex;

	std::vector<std::string>::iterator	_line;

	void	_setIndex(std::stringstream& ss);
	void	_setAutoindex(std::stringstream& ss);
	void	_setListen(std::stringstream& values);
	void	_setRoot(std::stringstream& values);
	void	_setServerName(std::stringstream& values);
	void	_setErrorPage(std::stringstream& values);
	void	_setClientSize(std::stringstream& values);
	void	_setLocation(std::vector<std::string>& inputFile, std::string prefix);
	std::string	_check_location(std::stringstream& ss) const;
};

std::ostream& operator<<(std::ostream& os, const Server& server);

#endif
