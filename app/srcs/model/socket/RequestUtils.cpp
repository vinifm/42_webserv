#include <Request.hpp>

std::string generate_autoindex(std::string path)
{
	std::string body;
	body.append("<h1>INDEX</h1>");
	DIR				*directory = opendir(path.c_str());
	struct dirent	*file;

	while ((file = readdir(directory)) != NULL)
	{
		if (std::string(file->d_name) == "." || std::string(file->d_name) == "..")
			continue ;
		std::stringstream buffer;
		std::string url = "/";
		url.append(std::string(file->d_name));
		buffer << "<a href=\"" << url <<"\">" << std::string(file->d_name) << "</a>";
		body.append(buffer.str());
	}
	closedir(directory);
	return (body);
}

std::string	load_file_bytes_in_body(std::string path)
{
	(void) path;
	std::ifstream file(path.c_str());
	 if (!file.is_open())
	{
		std::string msg;
		msg = "Load Page Error: Invalid Page Path! (";
		msg.append(path);
		msg.append(")");
		print_log("RequestUtils.cpp", msg);
	}
	std::stringstream buffer;
	buffer << file.rdbuf();
	return (buffer.str());
}

std::string	fix_route(Parser& parser, std::string route)
{
	if (route == "/" || route == "")
	{
		route = "./";
		route = route.append(parser.getRoot());
		add_final_bar(route);
	}
	if (route[0] == '/')
	{
		route = del_final_bar(parser.getRoot()).append(route);
	}
	return (route);
}

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
			std::string url = (*it);
			url = url.substr(0, url.find("\n") - 1);
			int	start = url.find_last_of(':');
			referer = url.substr(start, url.length());
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

std::string	extract_method(std::string url)
{
	std::vector<std::string>	*request_split;
	std::string					method="";

	request_split = ft_split(url, ' ');
	method = request_split->at(0);
	return (method);
}

std::string	add_final_bar(std::string root)
{
	if (root.empty())
		return (root);
	else
	{
		if (root[root.length() - 1] != '/')
			root.append("/");
	}
	return (root);
}

std::string	del_final_bar(std::string root)
{
	if (root.empty())
		return (root);
	else
	{
		if (root[root.length() - 1] == '/')
			root = root.substr(0, root.length() - 1);
	}
	return (root);
}

std::string	error_404(Response& response)
{
	(void) response;
	return ("<h1>404</h1>");
}

std::string	error_403(Response& response)
{
	(void) response;
	return ("<h1>403</h1>");
}