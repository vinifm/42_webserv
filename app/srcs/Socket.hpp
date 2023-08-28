#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <Utils.hpp>

class Socket
{
private:

	int						_endpoint_connection_socket_fd;
	struct sockaddr_in		_address_struct;
	int						_server_port;
	std::string				_server_root;

	char					_request_str[1024] = {0};
	std::string				_request_url;
	std::string				_request_server_name;
	std::string				_request_route;

	int						connection_socket_fd;

	std::string				_response_str;

public:
	//OCCF
	Socket(int server_port, std::string server_root);
	~Socket();

	//METHODS
	int				init();
	int				get_next_connection();
	int				request_is_valid();
	std::string		load_file();
	int				send_response(std::string root);
	int				reinit();
	int				deinit();
};

#endif
