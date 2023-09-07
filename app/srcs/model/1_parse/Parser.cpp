#include <Parser.hpp>

//occf
Parser::Parser(void)
{

}

Parser::~Parser(void)
{

}
Parser::Parser(std::string path)
{
	(void) path;
}

//methods
int Parser::is_valid(void)
{
	return (1);
}

//getters & setters
int	Parser::getPort(void)
{
	return (this->_port);
}

void	Parser::setPort(int port)
{
	this->_port = port;
}

std::string	Parser::getRoot(void)
{
	return (this->_root);
}

void	Parser::setRoot(std::string root)
{
	this->_root = root;
}
