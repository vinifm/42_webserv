#include <Utils.h>

std::string	getStr(void)
{
	return (this->_str);
}

void		setStr(std::string str)
{
	this->_str = str;
}

std::string	getRoute(void)
{
	return (this->_route);
}

void		setRoute(std::string route)
{
	this->_route = route;
}

std::string	getMethod(void)
{
	return (this->_method);
}

void		setMethod(std::string method)
{
	this->_method = method;
}
