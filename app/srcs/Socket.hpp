#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <Webserv.hpp>

//VARS
#define PORT 8080

class Socket
{
private:
	int						server_fd;
	struct sockaddr_in		server_configs;
	int						socket_fd;
	char					request_str[1024] = {0};

public:
	//OCCF
	Socket();
	~Socket();

	//METHODS
	int			init(int port);
	int			wait_request();
	int			is_valid_route();
	std::string	load_page(std::string path);
	int			send_response(std::string response);
	int			deinit();
};

#endif
