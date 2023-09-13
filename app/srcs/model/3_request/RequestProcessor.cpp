#include <Request.hpp>

std::string	 Request::execute_get(Parser& parser, Response& response)
{
	std::ostringstream	ss; ss << "(HTTP GET)"; print_log("RequestProcessor.cpp", ss.str(), 1);
	std::string			body="", route="";
	std::ostringstream	last_root_and_route;

	//1)EXTRAI A ROTA:
	this->setRoute(extract_route(this->_str.c_str()));
	route = this->getRoute();
	route = route.substr(1, route.length());
	route = del_final_bar(route);
	ss.str(""); ss << "("<< route << ") request route"; print_log("RequestProcessor.cpp", ss.str(), 1);

	//2)SE FOR O CASO, MUDA O LAST ROOT:
	int location_match_index = set_last_root(parser, this->_last_root, route);

	//3)APPEND ROOT + ROUTE:
	last_root_and_route.str("");
	this->_last_root = add_final_bar(this->_last_root);
	last_root_and_route << this->_last_root << route;
	ss.str(""); ss << "("<< this->_last_root << "|"<< route <<") full request route ("<< last_root_and_route.str() <<")"; print_log("RequestProcessor.cpp", ss.str(), 1);
	route = last_root_and_route.str();

	//4)GERA O BODY:
	body = serve_route(route, parser, location_match_index, *this, response);
	return (body);
}

std::string	Request::execute_post(Response& response)
{
	std::ostringstream ss; ss << "(HTTP POST)"; print_log("RequestProcessor.cpp", ss.str(), 1);
	std::ofstream	upload;
	std::string		upload_file_name = extract_file_name(this->_str);
	upload.open(std::string("./srcs/view/www/aws/").append(upload_file_name).c_str(), std::ios::binary);
	try
	{
		upload << extract_just_file_content(this->getBody());
	}
	catch(const std::exception& e)
	{
		response._statusLine->setCode(this->http_codes.find(400));
		std::cerr << e.what() << '\n';
	}
	upload.close();
	response._statusLine->setCode(this->http_codes.find(201));
	return ("");
}

std::string	Request::execute_delete(Response& response)
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
	return ("");
}

void	 Request::setResponseBody(Parser& parser, Response& response)
{
	std::string		body="";

	if (this->getMethod() == "GET")
		body = execute_get(parser, response);
	else if (this->getMethod() == "POST")
		body = execute_post(response);
	else if (this->getMethod() == "DELETE")
		body = execute_delete(response);
	response.setBody(body);
}

void	 Request::setResponseHeader(Response& response)
{
	response.setContentLength(response.getBody().length());
	response.buildHeader();
}
