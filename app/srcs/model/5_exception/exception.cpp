#include <Response.hpp>

void	init_http_codes(std::map<int, std::string>& http_codes)
{
	http_codes.insert(std::pair<int, std::string>(200, "OK"));
	http_codes.insert(std::pair<int, std::string>(201, "Created"));
	http_codes.insert(std::pair<int, std::string>(202, "Accepted"));
	http_codes.insert(std::pair<int, std::string>(204, "No Content"));
	http_codes.insert(std::pair<int, std::string>(300, "Multiple Choice"));
	http_codes.insert(std::pair<int, std::string>(301, "Moved Permanently"));
	http_codes.insert(std::pair<int, std::string>(302, "Found"));
	http_codes.insert(std::pair<int, std::string>(400, "Bad Request"));
	http_codes.insert(std::pair<int, std::string>(401, "Unauthorized"));
	http_codes.insert(std::pair<int, std::string>(403, "Forbidden"));
	http_codes.insert(std::pair<int, std::string>(404, "Not Found"));
	http_codes.insert(std::pair<int, std::string>(413, "Method Not Allowed"));
	http_codes.insert(std::pair<int, std::string>(415, "Request Entity Too Large"));
	http_codes.insert(std::pair<int, std::string>(500, "Unsupported Media Type"));
	http_codes.insert(std::pair<int, std::string>(502, "Bad Gateway"));
	http_codes.insert(std::pair<int, std::string>(504, "Gateway Timeout"));
	http_codes.insert(std::pair<int, std::string>(505, "HTTP Version Not Supported"));
}

std::string	error_404(Response& response)
{
	std::fstream file("srcs/view/www/_/404/index.html");
	std::stringstream body;

	body << file.rdbuf();
	(void) response;
	return (body.str());
}

std::string	error_403(Response& response)
{
	(void) response;
	return ("<h1>403</h1>");
}