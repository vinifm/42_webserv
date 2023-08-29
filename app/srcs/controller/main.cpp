#include <Utils.hpp>

void	requests_loop(Socket socket)
{
	while (true)
	{
		try
		{
			if (socket.get_next_connection())
				socket.send_response();
		}
		catch(const std::exception& e)
		{
			std::string 
			print_log("main.cpp", "Error: error exception was activated in socket");
		}
	}
}

int main(int argc, char **argv)
{
	//1) load_conf_file
	if (argc <= 1)
	{
		std::cout << "error: invalid number of args!" << std::endl;
		return (1);
	}
	ConfFile confFile(argv[1]);
	if (confFile.is_valid() == 0)
	{
		std::cout << "error: configuration file is invalid!" << std::endl;
		return (1);
	}
	print_banner();

	//2) if configuration file is ok, init socket using conf file datas
	Socket	socket(confFile);
	socket.init();

	//3) loop for process requests
	requests_loop(socket);

	//4)end_socket
	socket.deinit();
	return (0);
}
