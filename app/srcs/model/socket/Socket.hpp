#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <Utils.hpp>

class Socket
{
private:

	struct sockaddr_in		_address_struct;
	int						_endpoint_connection_socket_fd;
	int						_connection_socket_fd;
	ConfFile				_confFile;
	Request 				_request;

public:
	//********************
	//                   *
	//        OCCF       *
	//                   *
	//********************
	Socket(ConfFile confFile);
	~Socket();

	//********************
	//                   *
	//      METHODS      *
	//                   *
	//********************
	int				init();
	int				get_next_connection();
	int				send_response();
	int				reinit();
	int				deinit();
};

#endif
