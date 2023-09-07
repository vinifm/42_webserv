#include <Request.hpp>

std::string	 Request::execute_get(Parser& parser, Response& response)
{
	this->setRoute(extract_route(this->_str.c_str()));

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
			body = serve_route(new_route, &found_location, response);
			response.setBody(body);
			return (body);
		}
	}
	route = fix_route(parser, route);
	body = serve_route(route, &fake_location, response);
	return (body);
}

std::string	 Request::execute_post(Parser& parser, Response& response)
{
	std::ofstream	upload;
	std::string		upload_file_name = extract_file_name(this->_str);
	upload.open(std::string("./srcs/view/www/_/aws/").append(upload_file_name).c_str(), std::ios::binary);
	upload << extract_just_file_content(upload_file_name, this->_str);
	upload.close();
	(void) parser;
	(void) response;
	return ("");
}

std::string	 Request::execute_delete(Parser& parser, Response& response)
{
	(void) parser;
	(void) response;
	return ("");
}

void	 Request::setResponseBody(Parser& parser, Response& response)
{
	std::string		body="";

	if (this->getMethod() == "GET")
		body = execute_get(parser, response);
	else if (this->getMethod() == "POST")
		body = execute_post(parser, response);
	else if (this->getMethod() == "DELETE")
		body = execute_delete(parser, response);
	response.setBody(body);
}

void	 Request::setResponseHeader(Response& response)
{
	StatusLine statusLine("HTTP/1.1", this->http_codes.find(200), "OK");
	response.setStatusLine(statusLine);
	response.setContentLength(response.getBody().length());
	response.setLastModified("");
	response.setHeader(response.buildHeader());
}
