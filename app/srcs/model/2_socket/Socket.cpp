#include <Socket.hpp>

//occf
Socket::Socket(void)
{}

Socket::~Socket(void)
{}

Socket::Socket(Parser Parser)
{
	this-> _parser = Parser;
}

//methods
int	Socket::init(Listen _listen)
{
	init_http_codes(this->_request.http_codes);
	print_log("socket.cpp", "webserv on ✅", 1);
	if ((this->_server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		print_log("socket.cpp", "socket failed", 1);
		exit(EXIT_FAILURE);
	}
	std::ostringstream ss; ss << "(" << this->_server_fd << ") server_fd created"; print_log("socket.cpp", ss.str(), 1);

	int			opt = 1;
	if (setsockopt(this->_server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
	{
		print_log("socket.cpp", "setsockopt, port setting failed", 1);
		exit (EXIT_FAILURE);
	}
	fcntl(this->_server_fd, F_SETFL, O_NONBLOCK, FD_CLOEXEC);
	this->_address_struct.sin_family = AF_INET; // (IP family)
	this->_address_struct.sin_addr.s_addr = INADDR_ANY; // (localhost)
	this->_address_struct.sin_port = htons(_listen.getPort());
	if (bind(this->_server_fd, (struct sockaddr*) &this->_address_struct, sizeof(this->_address_struct)) < 0)
	{
		print_log("socket.cpp", "bind failed", 1);
		exit(EXIT_FAILURE);
	}
	ss.str("");ss << "(" << this->_server_fd << ") server binded to address (localhost) and port (" << _listen.getPort() << ")";print_log("socket.cpp", ss.str(), 1);

	if (listen(this->_server_fd, 3) < 0)
	{
		print_log("socket.cpp", "error setting listen", 1);
		exit(EXIT_FAILURE);
	}
	ss.str(""); ss << "(" << this->_server_fd << ") server setted to listen(passive) mode";print_log("socket.cpp", ss.str(), 1);
	this->_server_epoll_fd = epoll_create(1);
	this->_server_epoll_events.events = EPOLLIN;
	this->_server_epoll_events.data.fd = this->_server_fd;
	epoll_ctl(this->_server_epoll_fd, EPOLL_CTL_ADD, this->_server_fd, &this->_server_epoll_events);
	ss.str(""); ss << "(" << this->_server_epoll_fd << ") server epoll created";print_log("socket.cpp", ss.str(), 1);
	print_log("socket.cpp", "waiting for requests...", 1);
	return (0);
}

int	Socket::get_next_connection()
{
	int			addrlen = sizeof(this->_address_struct);

	if ((this->_client_fd = accept(this->_server_fd, (struct sockaddr*) &this->_address_struct, (socklen_t*)&addrlen)) < 0)
	{
		print_log("socket.cpp", "accept", 1);
		return (0);
	}
	return (this->_client_fd);
}

int	Socket::send_response(int e_client_fd)
{
	if (this->_request.toString().length() > 0)
	{
		Response response(this->_request.http_codes);
		this->requestProcessor().executeRequest(this->parserProcessor(), response);
		send(e_client_fd, response.toCString(), response.toString().length(), 0);
		std::ostringstream ss; ss << "("<< e_client_fd <<")" << " response sent to client"; print_log("socket.cpp", ss.str(), 1); print_log("", response.toString(), 0);
	}
	return (0);
}

int	Socket::deinit(void)
{
	shutdown(this->_server_fd, SHUT_RDWR);
	print_log("main.cpp", "webserv is off 🔴", 1);
	return (0);
}

//getters & setters
Request		Socket::requestProcessor(void)
{
	return (this->_request);
}

Parser		Socket::parserProcessor(void)
{
	return (this->_parser);
}

Request 	Socket::getRequest(void)
{
	return (this->_request);
}

void		Socket::setRequest(Request request)
{
	this->_request = request;
}

int		 	Socket::getServerFd(void)
{
	return (this->_server_fd);
}

void		Socket::setServerFd(int server_fd)
{
	this->_server_fd = server_fd;
}

struct epoll_event	Socket::getServerEpollEvents(void)
{
	return (this->_server_epoll_events);
}

void				Socket::setServerEpollEvents(struct epoll_event epoll_events)
{
	this->_server_epoll_events = epoll_events;
}

struct epoll_event	Socket::getEvent(int event)
{
	return (this->_events[event]);
}

struct epoll_event	*Socket::getEvents(void)
{
	return (this->_events);
}

int					Socket::getServerEpollFd(void)
{
	return (this->_server_epoll_fd);
}

void				Socket::setServerEpollFd(int server_epoll_fd)
{
	this->_server_epoll_fd = server_epoll_fd;
}
