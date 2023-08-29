#include <Request.hpp>

//occf
Request::Request(void)
{
}

Request::~Request(void)
{
}

Request::Request(std::string request_str)
{
	this->_str = request_str;
}

std::string	Request::toString(void)
{
	return (this->_str);
}

//utils
std::string	extract_route(std::string url)
{
	std::vector<std::string>	*request_split;
	std::string					route="";

	request_split = ft_split(url, ' ');
	route = request_split->at(1);
	return (route);
}

//getters & setters
void		Request::setStr(std::string str)
{
	this->_str = str;
}

std::string	Request::getRoute(void)
{
	return (this->_route);
}

void		Request::setRoute(std::string route)
{
	this->_route = route;
}

std::string	Request::getMethod(void)
{
	return (this->_method);
}

void		Request::setMethod(std::string method)
{
	this->_method = method;
}

//methods
void Request::extract(void)
{
	this->setRoute(extract_route(this->_str.c_str()));
}

int Request::executeRequest(void)
{
	
	return (0);
}

