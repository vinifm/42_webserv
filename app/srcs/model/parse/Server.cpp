#include "Server.hpp"

Server::Server() {}
Server::~Server() {}

void	Server::initServer(std::ifstream& inputFile)
{
	std::string	line;
	std::string	directive;

	while (std::getline(inputFile, line)) {
		std::stringstream ss(line);
		ss >> directive;
		if (directive.compare("listen") == 0)
			_setListen(ss);
		else if (directive.compare("root") == 0)
			_setRoot();
		else if (directive.compare("server_name") == 0)
			_setServerName();
		else if (directive.compare("error_page") == 0)
			_setErrorPage();
		else if (directive.compare("client_max_body_size") == 0)
			_setClientSize();
		else if (directive.compare("location") == 0)
			_setLocation();
		else if (line.compare("};") == 0)
			return ;
		else
			throw std::runtime_error("invalid directive");
	}
	throw std::runtime_error("unclosed server block");
}

void	Server::_setListen(const std::stringstream& values)
{
	Listen new_listen;
	new_listen.initListen(values);
	_listens.push_back(new_listen);
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
