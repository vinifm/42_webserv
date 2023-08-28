#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <unistd.h>

#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080

std::string	convert_page(std::string path)
{
	std::string http_header = " \
		'HTTP/1.1 200 OK'\n \
		'Content-Type: text/html; charset=UTF-8',\n \
		'Content-Encoding: UTF-8',\n \
		'Accept-Ranges: bytes',\n \
		'Connection: keep-alive',\n\n";

	std::string html = "<h1> HELLO WORLD transcendance ta chegando MY NAME IS SERVER </h1>";

	std::string response = http_header.append(html);
	return (response);
}

int main(void)
{
	int		server_fd, new_socket, valread;
	struct	sockaddr_in address;
	int		opt = 1;
	int		addrlen = sizeof(address);
	char	buffer[1024] = {0};
	std::string	response = convert_page("index.html"); 

	//printf("%s", response.c_str());
	
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("socket failed");
		exit(EXIT_FAILURE);
	}

	if (setsockopt(server_fd, SOL_SOCKET,
					SO_REUSEADDR | SO_REUSEPORT, &opt,
					sizeof(opt))) {
		perror("setsockopt, port setting failed");
		exit (EXIT_FAILURE);
	}
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);

	if (bind(server_fd, (struct sockaddr*) &address,
			sizeof(address)) < 0)
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	
	if (listen(server_fd, 3) < 0)
	{
		perror("listen");
		exit(EXIT_FAILURE);
	}
	
	while (true)
	{
		if ((new_socket = accept(server_fd, (struct sockaddr*) &address,
			(socklen_t*)&addrlen)) < 0)
		{
			perror("accept");
			exit(EXIT_FAILURE);
		}

		valread = read(new_socket, buffer, 1024);
		printf("%s\n", buffer);
		send(new_socket, response.c_str(),strlen(response.c_str()), 0);
		printf("Hello message sent\n");

		close(new_socket);
	
	}
	shutdown(server_fd, SHUT_RDWR);
	return (0);

}
