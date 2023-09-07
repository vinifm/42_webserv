#include <Response.hpp>
#include <Parser.hpp>
#include <Socket.hpp>

void	print_banner(void)
{
	std::string		path;
	std::fstream	file;
	std::string		line;

	path = "srcs/view/.banner";
	file.open(path.c_str());
	if (!file.is_open())
	{
		std::cout << "webserv banner file not found!" << std::endl;
		return ;
	}
	while (!file.eof())
	{
		getline(file, line);
		std::cout << BLUE << line << RESET_COLOR << std::endl;
	}
}

int main(int argc, char **argv)
{
	(void) argv;
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
	print_banner();
	Socket	socket(parser);
	socket.init();
	requests_loop(socket);
	socket.deinit();
	return (0);
}
