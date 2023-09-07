#include <Request.hpp>

std::string	extract_route(std::string request)
{
	std::string					route="";
	std::string					referer="";
	std::vector<std::string>	*request_split;

	request_split = NULL;
	request_split = ft_split(request, ' ');
	route = request_split->at(1);
	for(std::vector<std::string>::iterator it = (*request_split).begin(); it < (*request_split).end(); it++)
	{
		if ((*it).find("Referer:") != std::string::npos)
		{
			it++;
			std::string request = (*it);
			request = request.substr(0, request.find("\n") - 1);
			int	start = request.find_last_of(':');
			referer = request.substr(start, request.length());
			start = referer.find_first_of('/');
			referer = referer.substr(start, referer.length());
			if (referer == "/" || route.find(referer) != std::string::npos)
				break ;
			referer.append(route);
			return (referer);
		}
	}
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
	body = request.substr(limiter, request.length());
	return (body);
}

std::string	extract_file_name(std::string request)
{
	std::size_t start = request.find("filename=\"") + 10;
	std::string filename = request.substr(start, std::string(&(request.c_str()[start])).find("\""));
	return (filename);
}

std::string extract_just_file_content(std::string filename, std::string request)
{
	//1) get extension
	std::string extension = filename.substr(filename.find(".") + 1, filename.length());

	//2) get file content
	transform(extension.begin(), extension.end(), extension.begin(), ::toupper);
	std::string content = request.substr(request.find(extension) - 1, request.length());

	std::cout << "#" << content << "#" << std::endl;
	return (content);
}