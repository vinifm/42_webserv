#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <Conf.hpp>
#include <Request.hpp>
#include <Response.hpp>
#include <Utils.hpp>

class Socket
{
private:
	struct sockaddr_in		_address_struct;
	int						_endpoint_connection_socket_fd;
	int						_connection_socket_fd;
	Conf					_conf;
	Request 				_request;
	Response 				_response;

public:
	//occf
	Socket(void);
	~Socket(void);
	Socket(Conf Conf);

	//methods
	int				init(void);
	int				get_next_connection(void);
	int				send_response(void);
	int				clean_for_next_connection(void);
	int				deinit(void);

	//getters & setters
	Request	requestProcessor(void);

};

#endif
