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
		print_log("RequestUtils.cpp", msg, 1);
	}
	std::stringstream buffer;
	buffer << file.rdbuf();
	return (buffer.str());
}

std::string	serve_route(std::string route, Location *location, Request &request, Response& response)
{
	std::string	buffer;
	bool		autoindex;
	
	
	std::ostringstream ss; ss << "(" << route << ") trying to serve route";print_log("Request.cpp", ss.str(), 1);

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
				buffer = error_403(request, response);
		}
	}
	else if (file_exist(route))
		buffer = load_file_bytes_in_body(route);
	else
	{
		
		buffer = error_404(request, response);
	}
	return (buffer);
}