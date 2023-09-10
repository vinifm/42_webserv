#include <Request.hpp>

std::string	extract_route(std::string request)
{
	std::string					route="";
	std::string					referer="";
	std::vector<std::string>	*request_split;

	request_split = NULL;
	request_split = ft_split(request, ' ');
	route = request_split->at(1);
	return (route);
}

std::string	extract_method(std::string request)
{
	std::vector<std::string>	*request_split;
	std::string					method="";
	std::vector<std::string>	*route_split;

	request_split = ft_split(request, ' ');
	method = request_split->at(0);
	route_split = ft_split(request_split->at(1), '/');
	if (route_split->size() >= 1)
	{
		if (method == "POST" && route_split->at(0) == "delete")
			method = "DELETE";
	} 
	return (method);
}

std::string	extract_header(std::string request)
{
	std::string		header;
	std::size_t		limiter;

	limiter = request.find("\r\n\r\n");
	header = request.substr(0, limiter);
	return (header);
}

std::string	extract_body(std::string request)
{
	std::string		body;
	std::size_t		limiter;

	limiter = request.find("\r\n\r\n");
	body = request.substr(limiter + 2, request.length());
	for (int i = 0; i < 4; i++)
	{
		if (body[i] == '\n')
			body = body.erase(i, 1);
	}
	for (int i = 0; i < 4; i++)
	{
		if (body[i] == '\r')
			body = body.erase(i, 1);
	}
	return (body);
}

std::string	extract_file_name(std::string request)
{
	std::size_t start = request.find("filename=\"") + 10;
	std::string filename = request.substr(start, std::string(&(request.c_str()[start])).find("\""));
	return (filename);
}

std::string extract_just_file_content(std::string body)
{
	body = extract_body(body);
	return (body);
}

std::string	extract_delete_file_name(std::string delete_body)
{
	std::vector<std::string> *deletar = ft_split(delete_body, ':');
	std::string filename;
	if ((*deletar).size() > 1)
	{
		filename = (*deletar)[1];
		std::replace(filename.begin(), filename.end(), '+', ' ');
		filename = filename.substr(1);
		filename = filename.substr(0, filename.find("\"}"));
	}
	else
	{
		std::ostringstream ss; ss << "(" << delete_body << ") delete received wrong body"; print_log("RequestProcessor.cpp", ss.str(), 1);
		filename = "";
	}
	return (filename);
}