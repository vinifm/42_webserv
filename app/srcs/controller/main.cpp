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
		std::cout << WHITE << line << RESET_COLOR << std::endl;
	}
}

std::string Request::_last_root = "./srcs/view/www/";

int main(int argc, char **argv)
{
	Parser parser;
	if (argc != 2)
	{
		std::cerr << "error: invalid number of args!" << std::endl;
		return (1);
	}
	try {
		//PARSER
		parser.parseConfigFile(argv[1]);
		std::ostringstream ss; ss << parser << std::endl; print_log("", ss.str(), 0);
		exit(0);

		//REQUEST/RESPONSE
		print_banner();
		Socket	socket(parser);
		socket.init(parser.getServer(0).getListen(0));
		socket.getRequest().setLastRoot(add_final_bar(parser.getServer(0).getRoot()));
		requests_loop(socket);
		socket.deinit();
	}
	catch (std::exception& e) { std::cout << e.what() << std::endl; }
	return (0);
}
