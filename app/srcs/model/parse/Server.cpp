#include "Server.hpp"

Server::Server() {}
Server::~Server() {}

std::vector<std::string>::iterator& Server::initServer(std::vector<std::string>& inputFile,
	std::vector<std::string>::iterator& line)
{
	std::string	directive;
	std::string loc_prefix;

	for (_line = line; _line != inputFile.end(); ++_line) {
		std::stringstream ss(*_line);
		if (!(ss >> directive))
			continue;
		std::cout << "\tdirective: " << directive << std::endl;
		if (directive == "#")
			continue;
		else if (directive == "listen")
			_setListen(ss);
		else if (directive == "root")
			_setRoot();
		else if (directive == "index")
			_setIndex();
		else if (directive == "autoindex")
			_setAutoindex();
		else if (directive == "server_name")
			_setServerName();
		else if (directive == "error_page")
			_setErrorPage();
		else if (directive == "client_max_body_size")
			_setClientSize();
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
			// fechar fd
			std::cout << "Directive: " << directive << std::endl;
			throw std::runtime_error("Invalid server directive");
		}
		directive = "\0";
	}
	throw std::runtime_error("unclosed server block");
}

void	Server::_setListen(std::stringstream& values)
{
	Listen new_listen;
	new_listen.initListen(values);
	// _listens.push_back(new_listen);
}

void	Server::_setRoot()
{
}
void	Server::_setIndex()
{
}
void	Server::_setAutoindex()
{
}
void	Server::_setServerName()
{
}
void	Server::_setErrorPage()
{
}
void	Server::_setClientSize()
{
}
void	Server::_setLocation(std::vector<std::string>& inputFile, std::string prefix)
{
	Location new_location;
	_line = new_location.initLocation(inputFile, prefix, _line);
	_locations.push_back(new_location);
}

// std::ostream& operator<<(std::ostream& os, const Server& server)
// {
// 	os << "Listen: " << server.printAllListen() << std::endl
// 		<< "Server Names: " << server.printAllServerNames() << std::endl;
// 	return os;
// }

/*--- GETTERS ----------------------------------------------------------------*/

// void	Server::printAllListen() const
// {
// 	for (size_t i = 0; i < getListenSize(); ++i)
// 		std::cout << getListen(i) << std::endl;
// }
// Listen	Server::getListen(size_t index) const { return _listens.at(index); }
// size_t	Server::getListenSize() const { return _listens.size(); }

// void	Server::printAllServerNames() const
// {
// 	for (size_t i = 0; i < getServerNameSize(); ++i)
// 		std::cout << getServerName(i) << std::endl;
// }
// std::string	Server::getServerName(size_t index) const { return _serverNames.at(index); }
// size_t	Server::getServerNameSize() const { return _serverNames.size(); }

// void	Server::printAllLocation() const
// {
// 	for (size_t i = 0; i < getLocationSize(); ++i)
// 		std::cout << getLocation(i) << std::endl;
// }
// Location	Server::getLocation(size_t index) const { return _locations.at(index); }
// size_t		Server::getLocationSize() const { return _locations.size(); }

// void	Server::printAllIndex() const
// {
// 	for (size_t i = 0; i < getIndexSize(); ++i)
// 		std::cout << getIndex(i) << std::endl;
// }
// std::string	Server::getIndex(size_t index) const { return _index.at(index); }
// size_t		Server::getIndexSize() const { return _index.size(); }

