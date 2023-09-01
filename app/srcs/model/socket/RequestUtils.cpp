#include <Request.hpp>

std::string generate_autoindex(std::string path)
{
	(void) path;
	return (std::string("<h1>autoindex</h1>"));
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

std::string	extract_route(std::string url)
{
	std::vector<std::string>	*request_split;
	std::string					route="";

	request_split = ft_split(url, ' ');
	route = request_split->at(1);
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