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

//getters & setters
void		Request::setStr(std::string str)
{
	this->_str = str;
}

std::string	Request::getRoute(void)
{
	return (this->_route);
}

void		Request::setType(std::string type)
{
	this->_type = type;
}

std::string	Request::getType(void)
{
	return (this->_type);
}

void		Request::setRoute(std::string route)
{
	this->_route = route;
}

std::string	Request::getUploadFileName(void)
{
	return (this->_type);
}

void		Request::setUploadFileName(std::string upload_file_name)
{
	this->_upload_file_name = upload_file_name;
}

std::string	Request::getMethod(void)
{
	return (this->_method);
}

void		Request::setMethod(std::string method)
{
	this->_method = method;
}

std::string	Request::getBody(void)
{
	return (this->_body);
}

void		Request::setBody(std::string body)
{
	this->_body = body;
}

std::string	Request::getHeader(void)
{
	return (this->_header);
}

void		Request::setHeader(std::string header)
{
	this->_header = header;
}

// methods
int Request::executeRequest(Parser parser, Response& response)
{
	this->setBody(extract_body(this->_str));
	this->setHeader(extract_header(this->_str));
	this->setMethod(extract_method(this->getHeader()));

	this->setResponseBody(parser, response);
	this->setResponseHeader(response);
	execute_scripts(*this, response);
	response.buildResponse();
	return (0);
}

