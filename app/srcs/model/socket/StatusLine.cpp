#include <StatusLine.hpp>

//occf
StatusLine::StatusLine(void)
{
}

StatusLine::~StatusLine(void)
{
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
    return (this->_code.begin()->first);
}

std::string		StatusLine::getCodeMessage(void)
{
    return (this->_code.begin()->second);
}

void			StatusLine::setCode(std::map<int, std::string> code)
{
    this->_code = code;
}

std::string     StatusLine::toString(void)
{
    std::stringstream ss;

    ss << this->getProtocol() << " " << this->getCode() << " " << this->getResult();
    return(ss.str());
}