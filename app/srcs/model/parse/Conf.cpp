#include <Conf.hpp>

//occf
Conf::Conf(void)
{

}

Conf::~Conf(void)
{

}
Conf::Conf(std::string path)
{
	(void) path;
}

//methods
int Conf::is_valid(void)
{
	return (1);
}

//getters & setters
int	Conf::getPort(void)
{
	return (this->_port);
}

void	Conf::setPort(int port)
{
	this->_port = port;
}

std::string	Conf::getRoot(void)
{
	return (this->_root);
}

void	Conf::setRoot(std::string root)
{
	this->_root = root;
}