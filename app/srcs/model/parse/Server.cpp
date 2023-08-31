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
