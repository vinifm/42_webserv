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

int	receive_request(Socket& socket, int& e_client_fd)
{
	if (isSocketNonBlocking(e_client_fd) <= 0){std::ostringstream ss; ss << "Socket " << e_client_fd << " is blocking, fix it or errors may be generated"; print_log("socket.cpp", ss.str(), 1);return (1);}

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
		return (1);
	}
	else
	{
		std::ostringstream ss; ss << "(" << e_client_fd << ") request received";print_log("socket.cpp", ss.str(), 1);
		print_log("", full_request, 0);
		socket._request.setStr(full_request);
	}
	socket.send_response(e_client_fd);
	close(e_client_fd);
	print_log("socket.cpp", "waiting for requests...\n\n\n\n\n\n\n\n\n\n\n\n", 1);
	return (0);
}

void	requests_loop(Socket& socket)
{
	while (true)
	{
		int	n_requests = epoll_wait(socket.getServerEpollFd(), socket.getEvents(), MAX_EVENTS, -1); //wait requests in epoll server

		for (int i = 0; i < n_requests; i++)
		{
			try
			{
				if (socket.getEvent(i).data.fd == socket.getServerFd())
				{
					int	client_fd = socket.get_next_connection();
					fcntl(client_fd, F_SETFL, O_NONBLOCK, FD_CLOEXEC);
					// get client_fd, add it in spoll struct and add to epoll server:
					struct epoll_event client_event;
					client_event.events = EPOLLIN;
					client_event.data.fd = client_fd;
					epoll_ctl(socket.getServerEpollFd(), EPOLL_CTL_ADD, client_fd, &client_event);
				}
				else
				{
					if (socket.getEvent(i).events & EPOLLIN)
					{
						int e_client_fd = socket.getEvent(i).data.fd;
						if (receive_request(socket, e_client_fd))
							continue ;
					}
				}
			}
			catch(const std::exception& e)
			{
				std::ostringstream ss; ss << "(" << e.what() << ") epoll loop error"; print_log("main.cpp", ss.str(), 1);
				close(socket.getEvent(i).data.fd);
				continue ;
			}
		}
	}
}
