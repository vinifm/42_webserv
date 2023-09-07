#include <Socket.hpp>

int isSocketNonBlocking(int sockfd)
{
    int flags = fcntl(sockfd, F_GETFL, 0);

    if (flags == -1) {
        perror("fcntl");
        return -1; // Erro ao obter as flags do socket.
    }

    if (flags & O_NONBLOCK) {
	{
		std::ostringstream ss; ss << sockfd << " is non-blocking"; print_log("SocketUtils.cpp", ss.str(), 1);
        return 1; // O_NONBLOCK está definido, o socket é non-blocking.
	}
    } else {
		std::ostringstream ss; ss << sockfd << " is blocking"; print_log("SocketUtils.cpp", ss.str(), 1);
        return 0; // O_NONBLOCK não está definido, o socket é blocking.
    }
}

void	requests_loop(Socket& socket)
{
	while (true)
	{
		int	event_count = epoll_wait(socket._epoll_fd, socket._events, MAX_EVENTS, -1);

		for (int i = 0; i < event_count; i++)
		{
				try
				{
					if (socket._events[i].data.fd == socket._endpoint_connection_socket_fd)
					{
						// get next connection
						int	client_fd = socket.get_next_connection();
						fcntl(client_fd, F_SETFL, O_NONBLOCK, FD_CLOEXEC);

						// add new connection to epoll
						struct epoll_event client_event;
						client_event.events = EPOLLIN;
						client_event.data.fd = client_fd;
						epoll_ctl(socket._epoll_fd, EPOLL_CTL_ADD, client_fd, &client_event);
					}
					else
					{
						// execute request
						if (socket._events[i].events & EPOLLIN)
						{
							if (isSocketNonBlocking(socket._events[i].data.fd) <= 0)
							{
								std::ostringstream ss; ss << "Socket " << socket._events[i].data.fd << " is blocking, fix it or errors may be generated"; print_log("socket.cpp", ss.str(), 1);
								continue ;
							}

							// read first time, get request header and body
							char		buffer[1024];
							std::string	full_request="";
							int			bytes_read;

							bytes_read = 0;
							while (true)
							{
								bytes_read = recv(socket._events[i].data.fd, buffer, sizeof(buffer), 0);
								if (bytes_read <= 0)
									break ;
								full_request.append(buffer, bytes_read);
							}
							print_log("", full_request, 0);


							if (full_request.length() > 0)
							{
								socket._request.setStr(full_request);

								// execute request, send response
								Response response;
								socket.requestProcessor().executeRequest(socket.parserProcessor(), response);
								std::ostringstream ss; ss << "uri of connection identified by connect_pipe_fd (" << itos(socket._events[i].data.fd) << ") is valid, let's try to serve the root files"; print_log("socket.cpp", ss.str(), 1);
								send(socket._events[i].data.fd, response.toCString(), response.toString().length(), 0);
								ss.clear(); ss << "one response was sent to connection identified by _connection_socket_fd " << itos(socket._events[i].data.fd) << " and response is: "; print_log("socket.cpp", ss.str(), 1); print_log("", response.toString(), 0);
							}
							close(socket._events[i].data.fd);
						}
					}
				}
				catch(const std::exception& e)
				{
					std::ostringstream ss; ss << "Error: error exception was activated in socket (" << e.what() << ")";
					print_log("main.cpp", ss.str(), 1);
					close(socket._events[i].data.fd);
					continue ;
				}
		}
	}
}
