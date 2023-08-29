#include <ConfFile.hpp>

//occf
ConfFile(std::string path)
{
	(void) path;
}

//methods
int ConfFile::is_valid(void)
{
	return (1);
}

//getters & setters
int	ConfFile::getPort(void)
{
	return (this->_port);
}

int	ConfFile::setPort(int port)
{
	this->_port = port;
}

int	ConfFile::getRoot(void)
{
	return (this->_root);
}

int	ConfFile::setRoot(std::string root)
{
	this->_root = root;
}