#include <Socket.hpp>

/*****************
*                *
*      OCCF      *
*                *
*****************/
Socket::Socket(void)
{}

Socket::~Socket(void)
{}

Socket::Socket(Parser Parser) : _parser(Parser)
{}

/*****************
*                *
*    METHODS     *
*                *
*****************/

int	Socket::init()
{
	init_http_codes(this->_request.http_codes);

	std::string	msg;


	print_log("socket.cpp", "webserv is on ✅", 1);
	if ((this->_endpoint_connection_socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		print_log("socket.cpp", "socket failed", 1);
		exit(EXIT_FAILURE);
	}
	msg = "endpoint socket created successfuly (fd is ";
	msg.append(itos(this->_endpoint_connection_socket_fd));
	msg.append(")");
	print_log("socket.cpp", msg, 1);
	int			opt = 1;
	if (setsockopt(this->_endpoint_connection_socket_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
	{
		print_log("socket.cpp", "setsockopt, port setting failed", 1);
		exit (EXIT_FAILURE);
	}

	fcntl(this->_endpoint_connection_socket_fd, F_SETFL, O_NONBLOCK, FD_CLOEXEC);

	this->_address_struct.sin_family = AF_INET; // (IP family)
	this->_address_struct.sin_addr.s_addr = INADDR_ANY; // (localhost)
	this->_address_struct.sin_port = htons(this->_parser.getPort());
	if (bind(this->_endpoint_connection_socket_fd, (struct sockaddr*) &this->_address_struct, sizeof(this->_address_struct)) < 0)
	{
		print_log("socket.cpp", "bind failed", 1);
		exit(EXIT_FAILURE);
	}
	msg = "endpoint socket (fd ";
	msg.append(itos(this->_endpoint_connection_socket_fd));
	msg.append(") was binded with address (localhost) and port (");
	msg.append(itos(this->_parser.getPort()));
	msg.append(") successfully");
	print_log("socket.cpp", msg, 1);
	if (listen(this->_endpoint_connection_socket_fd, 3) < 0)
	{
		print_log("socket.cpp", "listen", 1);
		exit(EXIT_FAILURE);
	}

	this->_epoll_fd = epoll_create(1);

	this->_server_event.events = EPOLLIN;
	this->_server_event.data.fd = this->_endpoint_connection_socket_fd;
	epoll_ctl(this->_epoll_fd, EPOLL_CTL_ADD, this->_endpoint_connection_socket_fd, &this->_server_event);

	msg = "endpoint socket (fd ";
	msg.append(itos(this->_endpoint_connection_socket_fd));
	msg.append(") is now in listen(passive) mode! (Can't try connect, it will just receive connection requests)");
	print_log("socket.cpp", msg, 1);
	std::cout << std::endl;
	return (0);
}

int	Socket::get_next_connection()
{
	int			addrlen = sizeof(this->_address_struct);
	
	print_log("socket.cpp", "waiting a 'request' be done...", 1);
	if ((this->_connection_socket_fd = accept(this->_endpoint_connection_socket_fd, (struct sockaddr*) &this->_address_struct, (socklen_t*)&addrlen)) < 0)
	{
		print_log("socket.cpp", "accept", 1);
		return (0);
	}
	std::ostringstream ss; ss << "a new connection was started, _connection_socket_fd is " << itos(this->_connection_socket_fd) << " and 'request' is: " << std::endl;print_log("socket.cpp", ss.str(), 1);

	return (this->_connection_socket_fd);
}

int	Socket::send_response(Response &response)
{
	(void) response;
	return (0);
}

int	Socket::clean_for_next_connection()
{
	std::string	msg;

	// close(this->_connection_socket_fd);
	msg = "connection identified by _connection_socket_fd ";
	msg.append(itos(this->_connection_socket_fd));
	msg.append (" was closed");
	print_log("socket.cpp", msg, 1);
	this->_request.setRoute("");
	std::cout << std::endl;
	return (0);
}

int	Socket::deinit(void)
{
	print_log("socket.cpp", "endpoint socket was destroyed successfuly", 1);
	shutdown(this->_endpoint_connection_socket_fd, SHUT_RDWR);
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
