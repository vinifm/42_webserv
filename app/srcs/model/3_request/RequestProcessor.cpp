#include <Request.hpp>

std::string	 Request::execute_get(Parser& parser, Response& response)
{
	std::ostringstream ss; ss << "(HTTP GET)"; print_log("RequestProcessor.cpp", ss.str(), 1);
	this->setRoute(extract_route(this->_str.c_str()));
	std::string					body;
	Location					fake_location("/", parser.getRoot(), parser._autoindex);
	fake_location._index = parser._index;

	std::string					route = this->getRoute();
	std::vector<std::string>	*route_split = ft_split(route, '/');
std::cout << "**" << route << "***" << std::endl;

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
			std::cout << "----" << new_route << "-----" << std::endl;
			body = serve_route(new_route, &found_location, *this, response);
			response.setBody(body);
			return (body);
		}
		else
		{
			route = fix_route(parser, route);

			if (is_directory(route) == 0)
			{
				std::string find = (*route_split)[0];
				std::string aux = "/";
				aux.append(find);
				find = aux;
				std::string replace = "./srcs/view/www/404/";
				std::string new_route = route.replace(route.find(find), find.length(), replace);
				std::cout << "////" << new_route << "///////" << std::endl;
				Location flocation(route, new_route, 1);
				body = serve_route(new_route, &flocation, *this, response);
				response.setBody(body);
				return (body);
			}
		}
	}
	body = serve_route(route, &fake_location, *this, response);
	return (body);
}

std::string	 Request::execute_post(Parser& parser, Response& response)
{
	std::ostringstream ss; ss << "(HTTP POST)"; print_log("RequestProcessor.cpp", ss.str(), 1);
	std::ofstream	upload;
	std::string		upload_file_name = extract_file_name(this->_str);
	upload.open(std::string("./srcs/view/www/aws/").append(upload_file_name).c_str(), std::ios::binary);
	try
	{
		upload << extract_just_file_content(upload_file_name, this->_str);
		/* code */
	}
	catch(const std::exception& e)
	{
		response._statusLine->setCode(this->http_codes.find(400));
		std::cerr << e.what() << '\n';
	}
	
	upload.close();
	response._statusLine->setCode(this->http_codes.find(201));
	(void) parser;
	return ("");
}

std::string	 Request::execute_delete(Parser& parser, Response& response)
{
	std::ostringstream ss; ss << "(HTTP DELETE)"; print_log("RequestProcessor.cpp", ss.str(), 1);
	std::string file_to_delete = extract_delete_file_name(this->getBody());
	std::string del = std::string("./srcs/view/www/aws/").append(file_to_delete).c_str();
	if (std::remove(del.c_str()) == 0)
	{
		std::ostringstream ss; ss << "("<< del << ") file deleted"; print_log("RequestProcessor.cpp", ss.str(), 1);
		response._statusLine->setCode(this->http_codes.find(204));
	}
	else
	{
		std::ostringstream ss; ss << "("<< del << ") delete failed"; print_log("RequestProcessor.cpp", ss.str(), 1);
		perror("");
		response._statusLine->setCode(this->http_codes.find(400));
	}
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
	response.setContentLength(response.getBody().length());
	response.setLastModified("");
	response.buildHeader();
}
