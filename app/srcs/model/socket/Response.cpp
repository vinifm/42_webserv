#include <Response.hpp>

//occf
Response::Response(void)
{
}

Response::~Response(void)
{
}

//getters & setters
void			Response::setContentType(std::string contentType)
{
	this->_contentType = contentType;
}

std::string		Response::getContentType(void)
{
	return (this->_contentType);
}

void			Response::setContentLength(std::string contentLength)
{
	this->_contentLength = contentLength;
}

std::string		Response::getContentLength(void)
{
	return (this->_contentLength);
}

void			Response::setLastModified(std::string lastModified)
{
	this->_lastModified = lastModified;
}

std::string		Response::getLastModified(void)
{
	return (this->_lastModified);
}

void			Response::setHeader(std::string header)
{
	this->_header = header;
}

std::string		Response::getHeader(void)
{
	return (this->_header);
}

void			Response::setBody(std::string body)
{
	this->_body = body;
}

std::string		Response::getBody(void)
{
	return (this->_body);
}

void			Response::setStatusLine(StatusLine statusLine)
{
	this->_statusLine = statusLine;
}

StatusLine		Response::statusLineProcessor(void)
{
	return (this->_statusLine);
}

std::string		Response::toString(void)
{
	return (this->_str);
}

const char *Response::toCString(void)
{
	return (this->_str.c_str());
}
