#include "Parser.hpp"
// #include <Utils.hpp>

// void	requests_loop(Socket socket)
// {
// 	while (true)
// 	{
// 		try
// 		{
// 			if (socket.get_next_connection())
// 				socket.send_response();
// 		}
// 		catch(const std::exception& e)
// 		{
// 			print_log("main.cpp", "Error: error exception was activated in socket");
// 		}
// 	}
// }

int main(int argc, char **argv)
{
	Parser parser;
	//1) load_conf_file
	if (argc != 2)
	{
		std::cerr << "error: invalid number of args!" << std::endl;
		return (1);
	}
	try { parser.parseConfigFile(argv[1]); }
	catch (std::exception& e) { std::cout << e.what() << std::endl; }
		// if (parser.getIsValid() == false)
	// {
	// 	std::cerr << "error: configuration file is invalid!" << std::endl;
	// 	return (1);
	// }
	// print_banner();

	// //2) if configuration file is ok, init socket using conf file datas
	// Socket	socket(confFile);
	// socket.init();

	// //3) loop for process requests
	// requests_loop(socket);

	// //4)end_socket
	// socket.deinit();
	return (0);
}
