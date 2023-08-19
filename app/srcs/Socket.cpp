#include <Socket.hpp>

/*****************
*                *
*      OCCF      *
*                *
*****************/
Socket::Socket(int server_port, std::string server_root) : _server_port(server_port), _server_root(server_root)
{}

Socket::~Socket(void)
{}

/*****************
*                *
*      UTILS     *
*                *
*****************/
std::string	extract_url(std::string full_request)
{
	std::vector<std::string>			*request_split;
	std::vector<std::string>::iterator	it;
	size_t								found;
	std::string							url;
	
	request_split = ft_split(full_request, ' ');
	for (it = request_split->begin(); it < request_split->end(); it++)
	{
		found = (*it).find("http://", 0);
		if (found != std::string::npos)
		{
			url = (*it).substr(0, (*it).find("\n") - 1);
			return ((*it));
		}
	}
	return ("");
}

std::string	extract_route(std::string url)
{
	std::string	tmp;
	std::string	route;

	route = "";
	tmp = url.replace(0, 7, "");
	if (tmp.find("/") == std::string::npos)
		return ("");
	route = tmp.substr(tmp.find("/"), tmp.find("Accept-Encoding") - 16);
	return (route);
}

std::string	extract_server_name(std::string url)
{
	std::string	tmp;
	std::string	server_name;

	server_name = "";
	tmp = url.replace(0, 7, "");
	server_name = tmp.substr(0, tmp.find(":"));
	return (server_name);
}

/*****************
*                *
*    METHODS     *
*                *
*****************/
int	Socket::init()
{
	int		opt = 1;

	if ((this->_server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("socket failed");
		exit(EXIT_FAILURE);
	}

	if (setsockopt(this->_server_fd, SOL_SOCKET,
					SO_REUSEADDR | SO_REUSEPORT, &opt,
					sizeof(opt))) {
		perror("setsockopt, port setting failed");
		exit (EXIT_FAILURE);
	}
	this->_server_settings.sin_family = AF_INET;
	this->_server_settings.sin_addr.s_addr = INADDR_ANY;
	this->_server_settings.sin_port = htons(this->_server_port);

	if (bind(this->_server_fd, (struct sockaddr*) &this->_server_settings,
			sizeof(this->_server_settings)) < 0)
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}

	if (listen(this->_server_fd, 3) < 0)
	{
		perror("listen");
		exit(EXIT_FAILURE);
	}
	return (0);
}

int	Socket::wait_request()
{
	// CHECK IF THE SERVER RECEIVED SOME PACKEAGE
	int		addrlen = sizeof(this->_server_settings);
	int		n_bytes_read;
	
	if ((this->socket_fd = accept(this->_server_fd, (struct sockaddr*) &this->_server_settings, (socklen_t*)&addrlen)) < 0)
	{
		perror("accept");
		return (0);
	}
	n_bytes_read = read(this->socket_fd, this->_request_str, 1024);
	this->_request_url = extract_url(std::string (this->_request_str));
	this->_request_route = extract_route(this->_request_url);
	this->_request_server_name = extract_server_name(this->_request_url);
	return (1);
}

int	Socket::request_is_valid(void)
{
	// if (this->_request_route.empty())
	// 	return (0);
	std::cout << "#" << this->_request_route << "#" << std::endl;
	if (this->_request_route == "")
		return (1);
	return (1);
}

std::string	Socket::load_page()
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
	std::string		path;
	//CREATE PATH
	path = this->_server_root;
	path.append("index.html");
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

int	Socket::send_response(std::string root)
{
	std::cout << "server_route:" << this->_server_root << " & root: " << root << std::endl;
	// if (!root.empty())
	// 	this->_server_root = root;
	
	this->_response_str = this->load_page();
	if (this->_response_str.empty())
		return (0);
	send(this->socket_fd, this->_response_str.c_str(),strlen(this->_response_str.c_str()), 0);
	reinit();
	return (0);
}

int	Socket::reinit()
{
	close(this->socket_fd);
	this->_request_route = "";
	this->_request_url = "";
	this->_request_server_name = "";
	return (0);
}

int	Socket::deinit(void)
{
	shutdown(this->_server_fd, SHUT_RDWR);
	return (0);
}
