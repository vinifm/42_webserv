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
		std::string url = "";
		url.append(std::string(file->d_name));
		buffer << "<a href=\"" << url <<"\">" << std::string(file->d_name) << "</a><br>";
		body.append(buffer.str());
	}
	body.append("<br><br><a href=\"/\" class=\"btn btn-primary\">HOME</a>");
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

std::string	serve_route(std::string& route, Parser parser, int location_match_index, Request &request, Response& response)
{
	std::string	buffer;
	bool		autoindex;
	std::string index_found;

	if (is_directory(route))
	{
		if (location_match_index != -1) // if the route match a valid location
		{
			autoindex = parser.getServer(0).getLocation(location_match_index).getAutoindex();
			index_found = find_index_in_directory(parser.getServer(0).getLocation(location_match_index).getIndex(), route);
		}
		else // if the route match the default server configs
		{
			autoindex = parser.getServer(0).getAutoindex();
			index_found = find_index_in_directory(parser.getServer(0).getIndex(), route);
			std::cout << "--" << autoindex << "-|-" << index_found << "--" << std::endl;
		}

		if (!index_found.empty()) // se tiver pelo menos um arquivo dentro do index do location ou server
		{
			route.append(index_found);
			buffer = load_file_bytes_in_body(route);
			response.setLastModified(getLastModifiedDate(route));
			response.setContentType(getFileContentType(route));
		}
		else
		{
			if (autoindex == true)
			{
				buffer = generate_autoindex(route);
				request.setLastRoot(route);
			}
			else
				buffer = error_403(request, response);
		}
	}
	else if (file_exist(route))
	{
		buffer = load_file_bytes_in_body(route);
		response.setLastModified(getLastModifiedDate(route));
		response.setContentType(getFileContentType(route));
	}
	else
		buffer = error_404(request, response);
	return (buffer);
}
