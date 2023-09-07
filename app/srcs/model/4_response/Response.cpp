#include <Response.hpp>

//occf
Response::Response(void)
{
}

Response::~Response(void)
{
}

//methods
std::string	Response::buildHeader(void)
{
	std::stringstream buffer;
	buffer	<< this->getStatusLine().toString() << "\n"
			<< "Accept-Ranges: bytes\n"
			<< "Connection: close\n"
			<< "Content-Length:" << this->getContentLength() << "\n"
			<< "Content-Type:" << this->getContentType() << "\n"
			<< "Last-Modified:" << this->getLastModified() << "\n"
			<< "Server: webserv\n";
	return (buffer.str());
}

#include <stdlib.h>
std::string	Response::buildResponse(void)
{
	std::stringstream buffer;

	buffer << this->getHeader() << "\n" << this->getBody();
	this->_str = buffer.str();
	this->_length = this->_str.length();
	// std::cout << "#" << this->_str << "#" << std::endl;
	// exit(0);
	return (this->_str);
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

void			Response::setContentLength(int contentLength)
{
	this->_contentLength = contentLength;
}

int				Response::getContentLength(void)
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

void			Response::setBody(std::string body)
{
	this->_body = body;
}

std::string		Response::getBody(void)
{
	return (this->_body);
}

void			Response::setLength(int length)
{
	this->_length = length;
}

int				Response::getLength(void)
{
	return (this->_length);
}

void			Response::setStatusLine(StatusLine statusLine)
{
	this->_statusLine = statusLine;
}

StatusLine		Response::getStatusLine(void)
{
	return (this->_statusLine);
}

StatusLine		Response::statusLineProcessor(void)
{
	return (this->_statusLine);
}

void			Response::setHeader(std::string header)
{
	this->_header = header;
}

std::string			Response::getHeader(void)
{
	return (this->_header);
}

std::string		Response::toString(void)
{
	return (this->_str);
}

const char *Response::toCString(void)
{
	return (this->_str.c_str());
}
