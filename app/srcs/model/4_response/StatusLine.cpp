#include <StatusLine.hpp>

//occf
StatusLine::StatusLine(void)
{
	this->setProtocol("HTTP/1.1");
}

StatusLine::~StatusLine(void)
{
}

StatusLine::StatusLine(std::string protocol, std::map<int, std::string>::iterator code, std::string result)
{
	this->setProtocol(protocol);
	this->setCode(code);
	this->setResult(result);
}


//getters & setters
std::string		StatusLine::getProtocol(void)
{
	return (this->_protocol);
}

void			StatusLine::setProtocol(std::string protocol)
{
	this->_protocol = protocol;
}

std::string		StatusLine::getResult(void)
{
	return (this->_result);
}

void			StatusLine::setResult(std::string result)
{
	this->_result = result;
}

int				StatusLine::getCode(void)
{
	return (this->_code->first);
}

std::string		StatusLine::getCodeMessage(void)
{
	return (this->_code->second);
}

void			StatusLine::setCode(std::map<int, std::string>::iterator code)
{
	this->_code = code;
}

std::string     StatusLine::toString(void)
{
	std::stringstream ss;

	ss << this->getProtocol() << " " << this->getCode() << " " << this->getCodeMessage();
	return(ss.str());
}