#include "Server.hpp"

Server::Server() {}
Server::~Server() {}

std::vector<std::string>::iterator& Server::initServer(
	std::vector<std::string>& inputFile,
	std::vector<std::string>::iterator& line)
{
	std::string	directive;
	std::string loc_prefix;

	for (_line = line; _line != inputFile.end(); ++_line) {
		std::stringstream ss(*_line);
		if (!(ss >> directive))
			continue;
		if (directive == "#")
			continue;
		else if (directive == "listen")
			_setListen(ss);
		else if (directive == "server_name")
			_setServerName(ss);
		else if (directive == "root")
			_setRoot(ss);
		else if (directive == "client_max_body_size")
			_setClientSize(ss);
		else if (directive == "error_page")
			_setErrorPage(ss);
		else if (directive == "index")
			_setIndex(ss);
		else if (directive == "autoindex")
			_setAutoindex(ss);
		else if (directive == "location")
		{
			if (!(ss >> loc_prefix))
				throw std::runtime_error("location without prefix");
			_line++;
			_setLocation(inputFile, loc_prefix);
		}
		else if (*_line == "};")
			return _line;
		else
		{
			std::cout << "Directive: " << directive << std::endl;
			throw std::runtime_error("Invalid server directive");
		}
		directive = "\0";
	}
	throw std::runtime_error("unclosed server block");
}

/*--- SETTERS ----------------------------------------------------------------*/

void	Server::_setListen(std::stringstream& values)
{
	Listen new_listen;
	new_listen.initListen(values);
	_listens.push_back(new_listen);
}

void	Server::_setServerName(std::stringstream& values)
{
	std::string name;
	while (values >> name)
		_serverNames.push_back(name);
}

void	Server::_setRoot(std::stringstream& values)
{
	std::string	path;
	if (!(values >> path))
		throw std::runtime_error("Missing root path");
	char lastChar = path[path.length() - 1];
	if (lastChar != '/')
		throw std::runtime_error("root: path is not a directory");
	_root = path;
}

void	Server::_setClientSize(std::stringstream& values)
{
	std::string	size;
	if (!(values >> size))
		throw std::runtime_error("Missing max client body size");
	_client_max_body_size = size;
}

void	Server::_setErrorPage(std::stringstream& values)
{
	_error_pages.addPages(values);
}

void	Server::_setLocation(std::vector<std::string>& inputFile, std::string prefix)
{
	Location new_location;
	_line = new_location.initLocation(inputFile, prefix, _line);
	_locations.push_back(new_location);
}

void	Server::_setIndex(std::stringstream& ss)
{
	std::string	file;
	while (ss >> file)
		_index.push_back(file);
}

void	Server::_setAutoindex(std::stringstream& ss)
{
	std::string autoindex_option;
	ss >> autoindex_option;
	if (autoindex_option == "on")
		_autoindex = true;
	else if (autoindex_option == "off")
		_autoindex = false;
	else
		throw std::runtime_error("Invalid autoindex option");
}

/*--- GETTERS ----------------------------------------------------------------*/

Listen		Server::getListen(size_t index) const { return _listens.at(index); }
size_t		Server::getListenSize() const { return _listens.size(); }

std::string	Server::getServerName(size_t index) const { return _serverNames.at(index); }
size_t		Server::getServerNameSize() const { return _serverNames.size(); }

std::string	Server::getRoot() const { return _root; }
std::string	Server::getClientMaxBodySize() const { return _client_max_body_size; }

ErrorPages	Server::getErrorPages() const { return _error_pages; }

Location	Server::getLocation(size_t index) const { return _locations.at(index); }
size_t		Server::getLocationSize() const { return _locations.size(); }

std::vector<Location> Server::getLocations() const { return _locations; }

std::string	Server::getIndex(size_t index) const { return _index.at(index); }
size_t		Server::getIndexSize() const { return _index.size(); }
bool		Server::getAutoindex() const { return _autoindex; }
std::vector<std::string>	Server::getIndex() const { return _index; }

/*--- INSERTION OVERLOAD -----------------------------------------------------*/

std::ostream& operator<<(std::ostream& os, const Server& server)
{
	for (size_t i = 0; i < server.getListenSize(); ++i)
		os << server.getListen(i) << std::endl;

	os << "server_name:" << std::endl;
	for (size_t i = 0; i < server.getServerNameSize(); ++i) {
		os << "\t" << server.getServerName(i) << std::endl;
	}

	os << "root:\n\t" << server.getRoot() << std::endl;
	os << "client max body size:\n\t" << server.getClientMaxBodySize() << std::endl;
	os << server.getErrorPages() << std::endl;

	for (size_t i = 0; i < server.getLocationSize(); ++i) {
		os << MAGENTA << "LOCATION N." << i << RESET_COLOR << std::endl;
		os << server.getLocation(i) << std::endl;
	}
	return os;
}
