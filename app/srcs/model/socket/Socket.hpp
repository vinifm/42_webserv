#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <Parser.hpp>
#include <Request.hpp>
#include <Response.hpp>
#include <Webserv.hpp>

class Socket
{
private:
	struct sockaddr_in		_address_struct;
	int						_endpoint_connection_socket_fd;
	int						_connection_socket_fd;
	Parser					_parser;
	Request 				_request;

public:
	//occf
	Socket(void);
	~Socket(void);
	Socket(Parser parser);

	//methods
	int				init(void);
	int				get_next_connection(void);
	int				send_response(Response &response);
	int				clean_for_next_connection(void);
	int				deinit(void);

	//getters & setters
	Request		requestProcessor(void);
	Response	responseProcessor(void);
	Parser		parserProcessor(void);

};

#endif
