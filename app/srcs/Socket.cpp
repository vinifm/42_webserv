#include <Socket.hpp>

Socket::Socket(void)
{
}

Socket::~Socket(void)
{
}

int	Socket::init(int port)
{
	int		opt = 1;

	if ((this->server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("socket failed");
		exit(EXIT_FAILURE);
	}

	if (setsockopt(this->server_fd, SOL_SOCKET,
					SO_REUSEADDR | SO_REUSEPORT, &opt,
					sizeof(opt))) {
		perror("setsockopt, port setting failed");
		exit (EXIT_FAILURE);
	}
	this->server_configs.sin_family = AF_INET;
	this->server_configs.sin_addr.s_addr = INADDR_ANY;
	this->server_configs.sin_port = htons(port);

	if (bind(this->server_fd, (struct sockaddr*) &this->server_configs,
			sizeof(this->server_configs)) < 0)
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}

	if (listen(this->server_fd, 3) < 0)
	{
		perror("listen");
		exit(EXIT_FAILURE);
	}
	return (0);
}

int	Socket::wait_request()
{
	int		addrlen = sizeof(this->server_configs);
	int		valread;
	
	if ((this->socket_fd = accept(this->server_fd, (struct sockaddr*) &this->server_configs, (socklen_t*)&addrlen)) < 0)
	{
		perror("accept");
		return (0);
	}
	valread = read(this->socket_fd, this->request_str, 1024);
	return (1);
}

int	Socket::send_response(std::string response)
{
	send(this->socket_fd, response.c_str(),strlen(response.c_str()), 0);
	close(this->socket_fd);
	return (0);
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

int	Socket::deinit(void)
{
	shutdown(this->server_fd, SHUT_RDWR);
	return (0);
}