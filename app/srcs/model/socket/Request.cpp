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
	// this->setMethod();
	// this->setMethod();
	this->setRoute(extract_route(this->_str.c_str()));
}

int Request::executeRequest(Parser parser, Response& response)
{
	std::string	path;
	if (is_root(this->getRoute()))
		path = parser.getRoot().append("index.html");
	else
		path = parser.getRoot().append(this->getRoute());
	this->setResponseBody(path, response);
	this->setResponseHeader(response);
	response.buildResponse();
	return (0);
}

void	Request::setResponseHeader(Response& response)
{
	StatusLine statusLine("HTTP/1.1", g_http_codes->find(200), "OK");
	response.setStatusLine(statusLine);
	response.setContentLength(response.getBody().length());
	response.setLastModified("");
	response.setHeader(response.buildHeader());
}

void	Request::setResponseBody(std::string path, Response& response)
{
	if (is_root(this->getRoute()) || is_file(path))
	{
		this->setType("file");
		response.setBody(load_file_bytes_in_body(path));
	}
	if (is_directory(path))
	{
		this->setType("directory");
		response.setBody(generate_autoindex(path));
	}
	else
	{
		this->setType("404");
		error_404(response);
	}
}

