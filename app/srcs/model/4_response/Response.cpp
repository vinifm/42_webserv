#include <Response.hpp>

//occf
Response::Response(std::map<int, std::string> http_codes) : _http_codes(http_codes)
{
	this->_statusLine = new StatusLine();
	this->_statusLine->setProtocol("HTTP/1.1");
	this->_statusLine->setCode(this->_http_codes.find(200));
}

Response::~Response(void)
{
}

//methods
std::string	Response::buildHeader(void)
{
	std::stringstream buffer;
	buffer	<< this->_statusLine->toString() << "\n"
			<< "Accept-Ranges: bytes\n"
			<< "Connection: close\n"
			<< "Content-Length:" << this->getContentLength() << "\n"
			<< "Content-Type:" << this->getContentType() << "\n"
			<< "Last-Modified:" << this->getLastModified() << "\n"
			<< "Server: webserv\n";
	this->setHeader(buffer.str());
	return (buffer.str());
}

std::string	Response::buildResponse(void)
{
	std::stringstream buffer;

	buffer << this->getHeader() << "\n" << this->getBody();
	this->_str = buffer.str();
	this->setContentLength(this->toString().length());
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
