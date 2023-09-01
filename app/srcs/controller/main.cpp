#include <Request.hpp>
#include <Response.hpp>
#include <Socket.hpp>

std::map <int, std::string> *g_http_codes;

void	requests_loop(Socket socket)
{
	while (true)
	{
		try
		{
			if (socket.get_next_connection())
			{
				Response response;
				if (socket.requestProcessor().executeRequest(socket.parserProcessor(), response) == 0)
					socket.send_response(response);
			}
		}
		catch(const std::exception& e)
		{
			print_log("main.cpp", "Error: error exception was activated in socket");
		}
	}
}

void	init_parser_for_test(Parser& parser)
{
	parser.setPort(8080);
	parser.setRoot("srcs/view/www/default/");

	parser._location.push_back(Location("/", "srcs/view/www/default/", true));
	parser._location.push_back(Location("/image", "srcs/view/www/examples/serve_image_example/", false));
}


int main(int argc, char **argv)
{
	//0) setting http codes;
	std::map<int, std::string> http_codes;
	g_http_codes = &http_codes;

	//1) load_parser_file
	if (argc <= 1)
	{
		std::cout << "error: invalid number of args!" << std::endl;
		return (1);
	}
	Parser parser(argv[1]);

	if (parser.is_valid() == 0)
	{
		std::cout << "error:  file is invalid!" << std::endl;
		return (1);
	}
	init_parser_for_test(parser);

	std::cout << "#" << parser._location[1]._root << "#" << std::endl;
	print_banner();

	//2) if parseriguration file is ok, init socket using Parser file datas
	Socket	socket(parser);
	socket.init();

	//3) loop for process requests
	requests_loop(socket);

	//4)end_socket
	socket.deinit();
	return (0);
}
