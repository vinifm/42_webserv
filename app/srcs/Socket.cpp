#include <Socket.hpp>

/*****************
*                *
*      OCCF      *
*                *
*****************/
Socket::Socket(int server_port, std::string server_root) : _server_port(server_port), _server_root(server_root)
{}

Socket::~Socket(void)
{}

/*****************
*                *
*      UTILS     *
*                *
*****************/
std::string	extract_url(std::string full_request)
{
	std::vector<std::string>			*request_split;
	std::vector<std::string>::iterator	it;
	size_t								found;
	std::string							url;
	
	request_split = ft_split(full_request, ' ');
	for (it = request_split->begin(); it < request_split->end(); it++)
	{
		found = (*it).find("http://", 0);
		if (found != std::string::npos)
		{
			url = (*it).substr(0, (*it).find("\n") - 1);
			return ((*it));
		}
	}
	return ("");
}

std::string	extract_route(std::string url)
{
	std::string	tmp;
	std::string	route;

	route = "";
	tmp = url.replace(0, 7, "");
	if (tmp.find("/") == std::string::npos)
		return ("");
	route = tmp.substr(tmp.find("/"), tmp.find("Accept-Encoding") - 16);
	return (route);
}

std::string	extract_server_name(std::string url)
{
	std::string	tmp;
	std::string	server_name;

	server_name = "";
	tmp = url.replace(0, 7, "");
	server_name = tmp.substr(0, tmp.find(":"));
	return (server_name);
}

std::string	Socket::load_page()
{
	//VARS
	std::string		http_header = " \
		'HTTP/1.1 200 OK'\n \
		'Content-Type: text/html; charset=UTF-8',\n \
		'Content-Encoding: UTF-8',\n \
		'Accept-Ranges: bytes',\n \
		'Connection: keep-alive',\n\n";
	std::string		html;
	std::fstream	page_fd;
	std::string		path;
	//CREATE PATH
	path = this->_server_root;
	path.append("index.html");
	//PARSE PATH
	page_fd.open(path, std::ios::in);
	if (!page_fd.is_open())
	{
		print_log("socket.cpp", "Load Page Error: Invalid Page Path!");
		return (NULL);
	}
	//LOAD PATH
	while (!page_fd.eof())
	{
		std::string line;
		getline(page_fd, line);
		html.append(line);
		html.append("\n");
	}
	//PREPARE RESPONSE
	std::string response = http_header.append(html);
	return (response);
}

/*****************
*                *
*    METHODS     *
*                *
*****************/
int	Socket::init()
{
	std::string	msg;

	print_log("socket.cpp", "webserv is on ✅");
/////// 1) CREATE ENDPOINT_SOCKET;
	if ((this->_endpoint_connection_socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		print_log("socket.cpp", "socket failed");
		exit(EXIT_FAILURE);
	}
	msg = "endpoint socket created successfuly (fd is ";
	msg.append(itos(this->_endpoint_connection_socket_fd));
	msg.append(")");
	print_log("socket.cpp", msg);

/////// 2) MODIFY ENDPOINT_SOCKET BEHAVIOR;
	int			opt = 1;
	if (setsockopt(this->_endpoint_connection_socket_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
	{
		print_log("socket.cpp", "setsockopt, port setting failed");
		exit (EXIT_FAILURE);
	}

/////// 3) SET ADDRESS_STRUCTURE AND BIND ENDPOINT SOCKET;
	this->_address_struct.sin_family = AF_INET; // (IP family)
	this->_address_struct.sin_addr.s_addr = INADDR_ANY; // (localhost)
	this->_address_struct.sin_port = htons(this->_server_port);

	if (bind(this->_endpoint_connection_socket_fd, (struct sockaddr*) &this->_address_struct, sizeof(this->_address_struct)) < 0)
	{
		print_log("socket.cpp", "bind failed");
		exit(EXIT_FAILURE);
	}
	msg = "endpoint socket (fd ";
	msg.append(itos(this->_endpoint_connection_socket_fd));
	msg.append(") was binded with address (localhost) and port (");
	msg.append(itos(this->_server_port));
	msg.append(") successfully");
	print_log("socket.cpp", msg);

/////// 4) SET ENDPOINT_SOCKET AS PASSIVE MODE (JUST RECEIVE REQUEST);
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
/////// 5) EXTRACT FIRST CONNECTION OF (LISTENING PENDING CONNECTIONS 'QUEUE', GENERATED WHEN THE BROWSER TRY CONNECT() WITH SERVER);
	int		addrlen = sizeof(this->_address_struct);
	int		n_bytes_read;
	
	msg = "waiting a 'request' be done...";
	print_log("socket.cpp", msg);
	if ((this->connection_socket_fd = accept(this->_endpoint_connection_socket_fd, (struct sockaddr*) &this->_address_struct, (socklen_t*)&addrlen)) < 0)
	{
		print_log("socket.cpp", "accept");
		return (0);
	}
	msg = "a new connection was started, connection_socket_fd is ";
	msg.append(itos(this->connection_socket_fd));
	msg.append (" and 'request' is: \n\n");
	print_log("socket.cpp", msg);

/////// 6) EXTRACT URL, ROUTE, PORT, SERVERNAME FROM BROWSER REQUEST;
	n_bytes_read = read(this->connection_socket_fd, this->_request_str, 1024);
	this->_request_url = extract_url(std::string (this->_request_str));
	this->_request_route = extract_route(this->_request_url);
	this->_request_server_name = extract_server_name(this->_request_url);
	std::cout << this->_request_str << std::endl;
	return (1);
}

/////// 7) CHECK IF REQUEST IS VALID;
int	Socket::request_is_valid(void)
{
	std::string	msg;

	// if (this->_request_route.empty())
	// 	return (0);
	// std::cout << "#" << this->_request_route << "#" << std::endl;
	if (this->_request_route == "")
		return (1);
	msg = "uri of connection identified by connect_pipe_fd (";
	msg.append(itos(this->connection_socket_fd));
	msg.append (") is valid, let's try to serve the root files");
	print_log("socket.cpp", msg);
	return (1);
}


/////// 8) IF REQUEST IS VALID, SEND A VALID RESPONSE;
int	Socket::send_response(std::string root)
{
	std::string	msg;
	// std::cout << "server_route:" << this->_server_root << " & root: " << root << std::endl;
	// if (!root.empty())
	// 	this->_server_root = root;
	
	this->_response_str = this->load_page();
	if (this->_response_str.empty())
		return (0);
	send(this->connection_socket_fd, this->_response_str.c_str(),strlen(this->_response_str.c_str()), 0);
	msg = "one response was sent to connection identified by connection_socket_fd ";
	msg.append(itos(this->connection_socket_fd));
	msg.append(" and response is: ");
	print_log("socket.cpp", msg);
	std::cout << this->_response_str << std::endl;
	reinit();
	return (0);
}

/////// 9) PREPARE FOR A NEW CONNECTION;
int	Socket::reinit()
{
	std::string	msg;

	close(this->connection_socket_fd);
	msg = "connection identified by connection_socket_fd ";
	msg.append(itos(this->connection_socket_fd));
	msg.append (" was closed");
	print_log("socket.cpp", msg);
	this->_request_route = "";
	this->_request_url = "";
	this->_request_server_name = "";
	std::cout << std::endl;
	return (0);
}

/////// 10) SHUTDOWN ENDPOINT_SOCKET;
int	Socket::deinit(void)
{
	print_log("socket.cpp", "endpoint socket was destroyed successfuly");
	shutdown(this->_endpoint_connection_socket_fd, SHUT_RDWR);
	return (0);
}
