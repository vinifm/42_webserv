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
	std::string	msg;

	print_log("socket.cpp", "webserv is on ✅");
	if ((this->_endpoint_connection_socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		print_log("socket.cpp", "socket failed");
		exit(EXIT_FAILURE);
	}
	msg = "endpoint socket created successfuly (fd is ";
	msg.append(itos(this->_endpoint_connection_socket_fd));
	msg.append(")");
	print_log("socket.cpp", msg);
	int			opt = 1;
	if (setsockopt(this->_endpoint_connection_socket_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
	{
		print_log("socket.cpp", "setsockopt, port setting failed");
		exit (EXIT_FAILURE);
	}
	this->_address_struct.sin_family = AF_INET; // (IP family)
	this->_address_struct.sin_addr.s_addr = INADDR_ANY; // (localhost)
	this->_address_struct.sin_port = htons(this->_parser.getPort());
	if (bind(this->_endpoint_connection_socket_fd, (struct sockaddr*) &this->_address_struct, sizeof(this->_address_struct)) < 0)
	{
		print_log("socket.cpp", "bind failed");
		exit(EXIT_FAILURE);
	}
	msg = "endpoint socket (fd ";
	msg.append(itos(this->_endpoint_connection_socket_fd));
	msg.append(") was binded with address (localhost) and port (");
	msg.append(itos(this->_parser.getPort()));
	msg.append(") successfully");
	print_log("socket.cpp", msg);
	if (listen(this->_endpoint_connection_socket_fd, 3) < 0)
	{
		print_log("socket.cpp", "listen");
		exit(EXIT_FAILURE);
	}
	msg = "endpoint socket (fd ";
	msg.append(itos(this->_endpoint_connection_socket_fd));
	msg.append(") is now in listen(passive) mode! (Can't try connect, it will just receive connection requests)");
	print_log("socket.cpp", msg);
	std::cout << std::endl;
	return (0);
}

int	Socket::get_next_connection()
{
	std::string	msg;
	int			addrlen = sizeof(this->_address_struct);
	int			n_bytes_read;
	char		request_str[1024] = {0};
	std::string	tmp;
	
	msg = "waiting a 'request' be done...";
	print_log("socket.cpp", msg);
	if ((this->_connection_socket_fd = accept(this->_endpoint_connection_socket_fd, (struct sockaddr*) &this->_address_struct, (socklen_t*)&addrlen)) < 0)
	{
		print_log("socket.cpp", "accept");
		return (0);
	}
	msg = "a new connection was started, _connection_socket_fd is ";
	msg.append(itos(this->_connection_socket_fd));
	msg.append (" and 'request' is: \n\n");
	print_log("socket.cpp", msg);
	n_bytes_read = read(this->_connection_socket_fd, request_str, 1024);
	tmp = std::string(request_str);
	this->_request.setStr(tmp);
	std::cout << this->_request.toString() << std::endl;
	return (this->_connection_socket_fd);
}

int	Socket::send_response(Response &response)
{
	std::string	msg;

	msg = "uri of connection identified by connect_pipe_fd (";
	msg.append(itos(this->_connection_socket_fd));
	msg.append (") is valid, let's try to serve the root files");
	print_log("socket.cpp", msg);
	send(this->_connection_socket_fd, response.toCString(), response.getLength(), 0);
	msg = "one response was sent to connection identified by _connection_socket_fd ";
	msg.append(itos(this->_connection_socket_fd));
	msg.append(" and response is: ");
	print_log("socket.cpp", msg);
	std::cout << response.getHeader() << std::endl;
	return (0);
}

int	Socket::clean_for_next_connection()
{
	std::string	msg;

	close(this->_connection_socket_fd);
	msg = "connection identified by _connection_socket_fd ";
	msg.append(itos(this->_connection_socket_fd));
	msg.append (" was closed");
	print_log("socket.cpp", msg);
	this->_request.setRoute("");
	std::cout << std::endl;
	return (0);
}

int	Socket::deinit(void)
{
	print_log("socket.cpp", "endpoint socket was destroyed successfuly");
	shutdown(this->_endpoint_connection_socket_fd, SHUT_RDWR);
	print_log("main.cpp", "webserv is off 🔴");
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
