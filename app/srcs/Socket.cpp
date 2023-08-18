#include <Socket.hpp>

Socket::Socket(void)
{
}

Socket::~Socket(void)
{
}

std::string	Socket::load_page(std::string path)
{
	//VARS
	std::string		html;
	std::string		http_header = " \
		'HTTP/1.1 200 OK'\n \
		'Content-Type: text/html; charset=UTF-8',\n \
		'Content-Encoding: UTF-8',\n \
		'Accept-Ranges: bytes',\n \
		'Connection: keep-alive',\n\n";
	std::fstream	page_fd;
	//PARSE PATH
	page_fd.open(path, std::ios::in);
	if (!page_fd.is_open())
	{
		std::cout << "Load Page Error: Invalid Page Path!" << std::endl;
		return (NULL);
	}
	//LOAD PATH
	while (!page_fd.eof())
	{
		std::string line;
		getline(page_fd, line);
		html.append(line);
		html.append("\n");
	}
	//PREPARE RESPONSE
	std::string response = http_header.append(html);
	return (response);
}
