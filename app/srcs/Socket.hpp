#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <Webserv.hpp>

//VARS
#define PORT 8080

class Socket
{
private:

public:
	//OCCF
	Socket();
	~Socket();

	//GETTERS & SETTERS

	//METHODS
	std::string	load_page(std::string path);

};

#endif
