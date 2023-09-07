#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <Parser.hpp>
#include <Request.hpp>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <stdlib.h>
#include <cstring>

#define  MAX_EVENTS 10

class Socket
{
private:
	struct sockaddr_in		_address_struct;
	int						_client_fd;
	Parser					_parser;

public:
	Request 				_request;
	int						_server_fd;
	struct epoll_event		_server_epoll_events;
	struct epoll_event		_events[MAX_EVENTS];
	int						_server_epoll_fd;
	//occf
	Socket(void);
	~Socket(void);
	Socket(Parser parser);

	//methods
	int						init(void);
	int						get_next_connection(void);
	int						send_response(int e_client_fd);
	int						clean_for_next_connection(void);
	int						deinit(void);

	//getters & setters
	Request					requestProcessor(void);
	Response				responseProcessor(void);
	Parser					parserProcessor(void);
};

	int						isSocketNonBlocking(int sockfd);
	void					requests_loop(Socket& socket);

#endif
