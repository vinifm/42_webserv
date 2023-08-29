#include <Request.hpp>
#include <Response.hpp>
#include <Socket.hpp>

void	requests_loop(Socket socket)
{
	while (true)
	{
		try
		{
			if (socket.get_next_connection())
			{
				if (socket.requestProcessor().executeRequest() == 0)
					socket.send_response();
			}
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
	Conf conf(argv[1]);

	if (conf.is_valid() == 0)
	{
		std::cout << "error: configuration file is invalid!" << std::endl;
		return (1);
	}
	conf.setPort(8080);
	conf.setRoot("srcs/view/www/default");
	print_banner();

	//2) if configuration file is ok, init socket using conf file datas
	Socket	socket(conf);
	socket.init();

	//3) loop for process requests
	requests_loop(socket);

	//4)end_socket
	socket.deinit();
	return (0);
}
