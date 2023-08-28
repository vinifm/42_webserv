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
std::string	extract_route(std::string url)
{
	std::vector<std::string>	*request_split;
	std::string					route="";

	request_split = ft_split(url, ' ');
	route = request_split->at(1);
	return (route);
}

std::string		generate_header(std::string file, std::string content_type, int len)
{
	std::ostringstream	header;
	std::string			exit_status;

	exit_status = "200 OK";
	if (content_type.substr(0, 4) == "text")
	{
		header << " \
		'HTTP/1.1 "<< exit_status <<"'\n \
		'Content-Type:" << content_type <<"',\n \
		'Content-Encoding: UTF-8',\n \
		'Accept-Ranges: bytes',\n \
		'Connection: keep-alive',\n\n";
	}
	else
	{
		header << "\
HTTP/1.1 "<< exit_status <<"\n\
Accept-Ranges: bytes\n\
Connection: close\n\
Content-Length: " << len << "\n\
Content-Type: jpg\n\
Last-Modified: Mon, 28 Aug 2023 19:50:25 GMT\n\
Server: webserv\n\n";
	}
	return (header.str());
}

std::string	Socket::load_file()
{
	std::string		html;
	std::string		path;
	std::string 	msg;
	std::string		file_extension;

	//PARSE PATH
	std::string file;

	file = this->_request_route;
	if (file == "/")
		file = "index.html";
	else
		file = file.substr(1, file.length());

	// GET FILE EXTENSION
	file_extension = file.substr(file.find(".") + 1, file.length());
	path = this->_server_root;

	// CREATE COMPLETE FILE PATH
	path.append(file);

	// OPEN FILE
	std::ifstream	page_fd(path);
	// page_fd.open(path, std::ios::in);
	// if (!page_fd.is_open())
	// {
	// 	msg = "Load Page Error: Invalid Page Path! (";
	// 	msg.append(path);
	// 	msg.append(")");
	// 	print_log("socket.cpp", msg);
	// 	page_fd.open("www/404/index.html");
	// 	file_extension = "html";
	// }

	std::stringstream buffer;

	buffer << page_fd.rdbuf();

	

	std::string		content_type;
	// SET CONTENT-TYPE
	if (file_extension == "html" || file_extension == "css" || file_extension == "js" )
	{
		content_type = "text/";
		content_type.append(file_extension);
		content_type.append("; charset=UTF-8");
		html.append(generate_header(file, content_type, 0));

	}
	else if (file_extension == "jpg" || file_extension == "jpeg" || file_extension == "png" || file_extension == "bmp" || file_extension == "gif")
	{
		content_type = "image/";
		content_type.append(file_extension);
		html.append(generate_header(file, content_type, buffer.str().length()));

		// html.append(page_fd.rdbuf())
	}

	html.append(buffer.str());

	std::fstream saida;

	saida.open("saida", std::ios::out);
	saida << html;
	
	
		// while (!page_fd.eof())
		// {
		// 	std::string line;
		// 	getline(page_fd, line);
		// 	html.append(line);
		// 	html.append("\n");
		// }
	//GENERATE HEADER

	// std::cout << "#" << html << "#" << std::endl;
	//WRITE EACH LINE OF FILE INSIDE RESPONSE

		

	//MIX HEADER AND FILE CONTENT
		std::string response = html;
		// std::cout << html << std::endl;
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
	this->_request_route = extract_route(std::string (this->_request_str));
	std::cout << this->_request_str << std::endl;
	return (1);
}

/////// 8) IF REQUEST IS VALID, SEND A VALID RESPONSE;
int	Socket::send_response(std::string root)
{
	std::string	msg;
	
	msg = "uri of connection identified by connect_pipe_fd (";
	msg.append(itos(this->connection_socket_fd));
	msg.append (") is valid, let's try to serve the root files");
	print_log("socket.cpp", msg);
////////
	std::ifstream image ("www/default/server.jpg");
	
	std::stringstream buffer;

	buffer << image.rdbuf();

	std::stringstream response ="\
HTTP/1.1 200 OK\n\
Accept-Ranges: bytes\n\
Connection: close\n\
Content-Length: 6500\n\
Content-Type: jpg\n\
Last-Modified: Mon, 28 Aug 2023 19:50:25 GMT\n\
Server: webserv\n\n";

response << image.rdbuf();

this->_response_str = response.str();

////////
	this->_response_str = load_file();
	send(this->connection_socket_fd, this->_response_str.c_str(), strlen(this->_response_str.c_str()), 0);
	msg = "one response was sent to connection identified by connection_socket_fd ";
	msg.append(itos(this->connection_socket_fd));
	msg.append(" and response is: ");
	print_log("socket.cpp", msg);
	// std::cout << this->_response_str << std::endl;
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
