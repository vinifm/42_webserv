#include <Request.hpp>

std::string	fix_route(std::string route, Location *location)
{
	(void) location;
	if (route == "")
		route.append("index.html");
	return (route);
}

Location	*set_last_root(Parser &parser, std::string& _last_root, std::string& route, int& type)
{
	(void) parser;
	(void) route;
	(void) type;
	std::vector<std::string>	*route_split = ft_split(route, '/');
	std::vector<std::string>	split = (*route_split);
	Location *fake_location = new Location("/", parser.getRoot(), false);
	if (split.size() <= 0)
	{
		if (route == "")
			_last_root = parser.getRoot();
		return (fake_location);
	}
	// SERÁ QUE É UMA ROTA VÁLIDA E PRECISA MUDAR O SITE?
	std::string	first = split[0];
	Location *location = is_valid_location(std::string("/").append(first), parser);
	if (location && split.size() >= 1)
	{
		std::string find = (*location)._route;
		find = del_start_bar(find);
		route = route.replace(route.find(find), find.length(), "");
		route = del_start_bar(route);
	}
	if (location && split.size() >= 1)
	{
		if (_last_root.find((*location)._root) == std::string::npos)
			_last_root = (*location)._root;
		std::ostringstream ss;
		ss << _last_root << route;
		std::cout << "# location: " << (*location)._root << "\n" << "_last_root: " << _last_root << std::endl;

		return (location);
	}
	
	// if (location)
		// fake_location->_route = location->_route;
	return (fake_location);
}

/*
type=0 (erro)
type=1 (autoindex)
type=2 (file)
*/
std::string	 Request::execute_get(Parser& parser, Response& response)
{
	(void) response;

	std::ostringstream	ss; ss << "(HTTP GET)"; print_log("RequestProcessor.cpp", ss.str(), 1);
	std::string			body="", buffer="", route="";
	std::ostringstream	last_root_and_route;
	int					type=2;
	Location			*location = NULL;

	//1)EXTRAI A ROTA:
	this->setRoute(extract_route(this->_str.c_str()));
	route = this->getRoute();
	route = route.substr(1, route.length());
	route = del_final_bar(route);
	ss.str(""); ss << "("<< route << ") request route"; print_log("RequestProcessor.cpp", ss.str(), 1);

	//2)SE FOR O CASO, MUDA O LAST ROOT:
	location = set_last_root(parser, this->_last_root, route, type);

	//3)SE FOR O CASO, ADICIONA O PRIMEIRO INDEX.HTML:
	// route = fix_route(route, location);

	//4)APPEND:
	last_root_and_route.str("");
	this->_last_root = add_final_bar(this->_last_root);
	last_root_and_route << this->_last_root << route;
	ss.str(""); ss << "("<< this->_last_root << "|"<< route <<") full request route"; print_log("RequestProcessor.cpp", ss.str(), 1);
	route = last_root_and_route.str();


	std::cout << "---" << route << "----" << std::endl;
	//5)DEPENDENDO DO TIPO DE REQUISIÇÃO, GERA O BODY:
	body = serve_route(route, location, *this, response);

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
		upload << extract_just_file_content(this->getBody());
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
