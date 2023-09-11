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
	int						_server_epoll_fd;
	struct epoll_event		_events[MAX_EVENTS];

	//occf
	Socket(void);
	~Socket(void);
	Socket(Parser parser);

	//methods
	int						init(Listen listen);
	int						get_next_connection(void);
	int						send_response(int e_client_fd);
	int						clean_for_next_connection(void);
	int						deinit(void);

	//getters & setters
	Request					requestProcessor(void);
	Response				responseProcessor(void);
	Parser					parserProcessor(void);
	Request 				getRequest(void);
	void					setRequest(Request request);
	int 	 				getServerFd(void);
	void					setServerFd(int server_fd);
	struct epoll_event		getServerEpollEvents(void);
	void					setServerEpollEvents(struct epoll_event epoll_events);
	struct epoll_event		getEvent(int event);
	struct epoll_event		*getEvents(void);
	void					setEvent(struct epoll_event events);
	int						getServerEpollFd(void);
	void					setServerEpollFd(int server_epoll_fd);
};

	int						isSocketNonBlocking(int sockfd);
	void					requests_loop(Socket& socket);

#endif
