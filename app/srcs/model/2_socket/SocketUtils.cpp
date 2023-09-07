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
		// std::ostringstream ss; ss << "(" << sockfd << ") client_fd is non-blocking"; print_log("SocketUtils.cpp", ss.str(), 1);
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
		int	event_count = epoll_wait(socket._server_epoll_fd, socket._events, MAX_EVENTS, -1);

		for (int i = 0; i < event_count; i++)
		{
				try
				{
					if (socket._events[i].data.fd == socket._server_fd)
					{
						// get next connection
						int	client_fd = socket.get_next_connection();
						fcntl(client_fd, F_SETFL, O_NONBLOCK, FD_CLOEXEC);

						// add new connection to epoll
						struct epoll_event client_event;
						client_event.events = EPOLLIN;
						client_event.data.fd = client_fd;
						epoll_ctl(socket._server_epoll_fd, EPOLL_CTL_ADD, client_fd, &client_event);
					}
					else
					{
						// execute request
						if (socket._events[i].events & EPOLLIN)
						{
							int e_client_fd = socket._events[i].data.fd;
							if (isSocketNonBlocking(e_client_fd) <= 0)
							{
								std::ostringstream ss; ss << "Socket " << e_client_fd << " is blocking, fix it or errors may be generated"; print_log("socket.cpp", ss.str(), 1);
								continue ;
							}

							char		buffer[1024];
							std::string	full_request="";
							int			bytes_read;

							bytes_read = 0;
							while (true)
							{
								bytes_read = recv(e_client_fd, buffer, sizeof(buffer), 0);
								if (bytes_read <= 0)
									break ;
								full_request.append(buffer, bytes_read);
							}
							if (full_request.length() <= 0)
							{
								close (e_client_fd);
								continue ;
							}
							std::ostringstream ss; ss << "(" << e_client_fd << ") request received";print_log("socket.cpp", ss.str(), 1);
							print_log("", full_request, 0);
							socket._request.setStr(full_request);
							socket.send_response(e_client_fd);
							close(e_client_fd);
							print_log("socket.cpp", "waiting for requests...", 1);
							std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n" << std::endl;
						}
					}
				}
				catch(const std::exception& e)
				{
					std::ostringstream ss; ss << "Error: error exception was activated in socket (" << e.what() << ")"; print_log("main.cpp", ss.str(), 1);
					close(socket._events[i].data.fd);
					continue ;
				}
		}
	}
}
