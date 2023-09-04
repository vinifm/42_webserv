#include "Server.hpp"

Server::Server() {}
Server::~Server() {}

void	Server::initServer(std::ifstream& inputFile)
{
	std::string	line;
	std::string	directive;

	while (std::getline(inputFile, line)) {
		std::stringstream ss(line);
		if (!(ss >> directive))
			continue;
		std::cout << "directive: " << directive << std::endl;
		if (directive == "listen")
			_setListen(ss);
		else if (directive == "root")
			_setRoot();
		else if (directive == "server_name")
			_setServerName();
		else if (directive == "error_page")
			_setErrorPage();
		else if (directive == "client_max_body_size")
			_setClientSize();
		else if (directive == "location")
			_setLocation();
		else if (line == "};")
			return ;
		else
			// fechar fd
			throw std::runtime_error("invalid directive");
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
void	Server::_setServerName()
{
}
void	Server::_setErrorPage()
{
}
void	Server::_setClientSize()
{
}
void	Server::_setLocation()
{
}


std::ostream& operator<<(std::ostream& os, const Server& server)
{
	std::cout << "Listen: " << server.printAllListen() << std::endl
		<< "Server Names: " << server.printAllServerNames() << std::endl;
}

/*--- GETTERS ----------------------------------------------------------------*/

void	Server::printAllListen() const
{
	for (size_t i = 0; i < getListenSize(); ++i)
		std::cout << getListen(i) << std::endl;
}
Listen	Server::getListen(size_t index) const { return _listens.at(index); }
size_t	Server::getListenSize() const { return _listens.size(); }

void	Server::printAllServerNames() const
{
	for (size_t i = 0; i < getServerNameSize(); ++i)
		std::cout << getServerName(i) << std::endl;
}
std::string	Server::getServerName(size_t index) const { return _serverNames.at(index); }
size_t	Server::getServerNameSize() const { return _serverNames.size(); }

void	Server::printAllLocation() const
{
	for (size_t i = 0; i < getLocationSize(); ++i)
		std::cout << getLocation(i) << std::endl;
}
Location	Server::getLocation(size_t index) const { return _locations.at(index); }
size_t		Server::getLocationSize() const { return _locations.size(); }

void	Server::printAllIndex() const
{
	for (size_t i = 0; i < getIndexSize(); ++i)
		std::cout << getIndex(i) << std::endl;
}
std::string	Server::getIndex(size_t index) const { return _index.at(index); }
size_t		Server::getIndexSize() const { return _index.size(); }

