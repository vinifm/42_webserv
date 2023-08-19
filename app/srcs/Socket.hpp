#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <Utils.hpp>

class Socket
{
private:

	int						_server_fd;
	struct sockaddr_in		_server_settings;
	int						_server_port;
	std::string				_server_root;

	char					_request_str[1024] = {0};
	std::string				_request_url;
	std::string				_request_server_name;
	std::string				_request_route;

	int						socket_fd;

	std::string				_response_str;

public:
	//OCCF
	Socket(int server_port, std::string server_root);
	~Socket();

	//METHODS
	int				init();
	int				wait_request();
	int				request_is_valid();
	std::string		load_page();
	int				send_response(std::string root);
	int				reinit();
	int				deinit();
};

#endif
