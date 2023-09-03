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

int Request::executeRequest(Parser parser, Response& response)
{
	this->setRoute(extract_route(this->_str.c_str()));
	this->setResponseBody(parser, response);
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

// setResponseBody ------>

static	int	is_valid_location(std::string route, Parser& parser) // check if passed route exist in some location on Parser class;
{
	int	index_location = 0;

	for (std::vector<Location>::iterator it = parser._location.begin(); it < parser._location.end(); it++)
	{
		if (route == it->_route)
			return (index_location);
		index_location++;
	}
	return (-1);
}

std::string find_index_in_directory(std::vector<std::string> index, std::string path)
{
	/*
		1) LOOP THE DIRECTORY LIST OF FILES TRYING TO FIND SOME STRING INSIDE INDEX;
	*/
	DIR				*directory = opendir(path.c_str());
	struct dirent	*file;

	while ((file = readdir(directory)) != NULL)
	{
		for (std::vector<std::string>::iterator it = index.begin(); it < index.end(); it++)
		{
			if (std::string(file->d_name) == *it)
			{
				closedir(directory);
				return (*it);
			}
		}
	}
	closedir(directory);
	return ("");
}

static	std::string	serve_route(std::string route, Location *location, Response& response)
{
	std::string	buffer;
	bool	autoindex;

	autoindex = location->_autoindex;
	if (is_directory(route))
	{
		std::string index_found = find_index_in_directory(location->_index, route);
		if (!index_found.empty())
		{
			route.append(index_found);
			buffer = load_file_bytes_in_body(route);
		}
		else
		{
			if (autoindex == true)
				buffer = generate_autoindex(route);
			else
				buffer = error_403(response);
		}
	}
	else if (file_exist(route))
		buffer = load_file_bytes_in_body(route);
	else
		buffer = error_404(response);
	return (buffer);
}

void	Request::setResponseBody(Parser& parser, Response& response)
{
	std::string					body;
	Location					fake_location("/", parser.getRoot(), parser._autoindex);
	fake_location._index = parser._index;

	std::string					route = this->getRoute();
	std::vector<std::string>	*route_split = ft_split(route, '/');

	if ((*route_split).size() >= 1)
	{
		int	location_index = -1;
		std::string aux = "/";
		aux.append((*route_split)[0]);
		location_index = is_valid_location(aux, parser);
		if (location_index != -1) // try serve route 'x' that is a location
		{
			Location found_location = parser._location[location_index];
			std::string find = found_location._route.substr(1, parser._location[location_index]._route.length());
			std::string aux = "/";
			aux.append(find);
			find = aux;
			std::string replace = found_location._root;
			std::string new_route = route.replace(route.find(find), find.length(), replace);
			std::cout << "find:" << find << std::endl;
			std::cout << "replace:" << replace << std::endl;
			std::cout << "new_rote:" << new_route << std::endl;
			body = serve_route(new_route, &found_location, response);
			response.setBody(body);
			return ;
		}
	}
	route = fix_route(parser, route);
	body = serve_route(route, &fake_location, response);
	response.setBody(body);
}
