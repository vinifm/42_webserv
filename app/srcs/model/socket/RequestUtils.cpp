#include <Request.hpp>

int is_directory(std::string path)
{
    (void) path;
    return (0);
}

int is_file(std::string path)
{
    (void) path;
    return (1);
}

std::string generate_autoindex()
{
    return (std::string("<h1>autoindex</h1>"));
}

/*****************
*                *
*      UTILS     *
*                *
*****************/
// 	std::string	msg;
	
// 	msg = "uri of connection identified by connect_pipe_fd (";
// 	msg.append(itos(this->_connection_socket_fd));
// 	msg.append (") is valid, let's try to serve the root files");
// 	print_log("socket.cpp", msg);
// 	std::ifstream image ("www/default/server.jpg");
// 	std::stringstream buffer;
// 	buffer << image.rdbuf();
// 	std::stringstream response;
// 	response << "\
// 	HTTP/1.1 200 OK\n\
// 	Accept-Ranges: bytes\n\
// 	Connection: close\n\
// 	Content-Length: 6500\n\
// 	Content-Type: jpg\n\
// 	Last-Modified: Mon, 28 Aug 2023 19:50:25 GMT\n\
// 	Server: webserv\n\n";
// 	response << image.rdbuf();
// 	this->_response_str = response.str();
// 	this->_response_str = load_file();
// 	send(this->_connection_socket_fd, this->_response_str.c_str(), strlen(this->_response_str.c_str()), 0);
// 	msg = "one response was sent to connection identified by _connection_socket_fd ";
// 	msg.append(itos(this->_connection_socket_fd));
// 	msg.append(" and response is: ");
// 	print_log("socket.cpp", msg);
// 	// std::cout << this->_response_str << std::endl;
// 	reinit();

// std::string		generate_header(std::string content_type, int len)
// {
// 	std::ostringstream	header;
// 	std::string			exit_status;

// 	exit_status = "200 OK";
// 	if (content_type.substr(0, 4) == "text")
// 	{
// 		header << " \
// 		'HTTP/1.1 "<< exit_status <<"'\n \
// 		'Content-Type:" << content_type <<"',\n \
// 		'Content-Encoding: UTF-8',\n \
// 		'Accept-Ranges: bytes',\n \
// 		'Connection: keep-alive',\n\n";
// 	}
// 	else
// 	{
// 		header << "\
// HTTP/1.1 "<< exit_status <<"\n\
// Accept-Ranges: bytes\n\
// Connection: close\n\
// Content-Length: " << len << "\n\
// Content-Type: jpg\n\
// Last-Modified: Mon, 28 Aug 2023 19:50:25 GMT\n\
// Server: webserv\n\n";
// 	}
// 	return (header.str());
// }

// std::string	Socket::load_file()
// {
// 	std::string		html;
// 	std::string		path;
// 	std::string 	msg;
// 	std::string		file_extension;

// 	//PARSE PATH
// 	std::string file;

// 	file = this->_request_route;
// 	if (file == "/")
// 		file = "index.html";
// 	else
// 		file = file.substr(1, file.length());

// 	// GET FILE EXTENSION
// 	file_extension = file.substr(file.find(".") + 1, file.length());
// 	path = this->_server_root;

// 	// CREATE COMPLETE FILE PATH
// 	path.append(file);

// 	// OPEN FILE
// 	// std::ifstream	page_fd(path);
// 	// page_fd.open(path, std::ios::in);
// 	// if (!page_fd.is_open())
// 	// {
// 	// 	msg = "Load Page Error: Invalid Page Path! (";
// 	// 	msg.append(path);
// 	// 	msg.append(")");
// 	// 	print_log("socket.cpp", msg);
// 	// 	page_fd.open("www/404/index.html");
// 	// 	file_extension = "html";
// 	// }

// 	std::stringstream buffer;

// 	// buffer << page_fd.rdbuf();

	

// 	std::string		content_type;
// 	// SET CONTENT-TYPE
// 	if (file_extension == "html" || file_extension == "css" || file_extension == "js" )
// 	{
// 		content_type = "text/";
// 		content_type.append(file_extension);
// 		content_type.append("; charset=UTF-8");
// 		html.append(generate_header(content_type, 0));

// 	}
// 	else if (file_extension == "jpg" || file_extension == "jpeg" || file_extension == "png" || file_extension == "bmp" || file_extension == "gif")
// 	{
// 		content_type = "image/";
// 		content_type.append(file_extension);
// 		html.append(generate_header(content_type, buffer.str().length()));

// 		// html.append(page_fd.rdbuf())
// 	}

// 	html.append(buffer.str());

// 	std::fstream saida;

// 	saida.open("saida", std::ios::out);
// 	saida << html;
	
	
// 		// while (!page_fd.eof())
// 		// {
// 		// 	std::string line;
// 		// 	getline(page_fd, line);
// 		// 	html.append(line);
// 		// 	html.append("\n");
// 		// }
// 	//GENERATE HEADER

// 	// std::cout << "#" << html << "#" << std::endl;
// 	//WRITE EACH LINE OF FILE INSIDE RESPONSE

		

// 	//MIX HEADER AND FILE CONTENT
// 		std::string response = html;
// 		// std::cout << html << std::endl;
// 	return (response);
// }