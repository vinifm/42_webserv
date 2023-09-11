#include <Parser.hpp>

// void	init_parser_for_test(Parser& parser)
// {
// 	parser.setPort(8080);
// 	parser.setRoot("srcs/view/www/default/");
// 	parser._index.push_back("index.html");
// 	parser._index.push_back("index.php");
// 	parser._location.push_back(Location("/", "srcs/view/www/default/", true));
// 	parser._location.push_back(Location("/delete", "srcs/view/www/delete/", false));
// 	parser._location.push_back(Location("/upload", "srcs/view/www/upload/", false));
// 	parser._location.push_back(Location("/autoindex", "srcs/view/www/autoindex/", true));
// 	parser._location.push_back(Location("/forbidden", "srcs/view/www/autoindex/", false));
// 	parser._location.push_back(Location("/redition", "srcs/view/www/redirection/", false));
// 	parser._location.push_back(Location("/cgi", "srcs/view/www/cgi/", false));
// 	parser._location.push_back(Location("/aws", "srcs/view/www/aws/", false));
// }

std::vector<std::string> *ft_split(std::string str, char delimiter)
{
	size_t start = 0;
	size_t end = 0;
	std::vector<std::string> *out;

	out = new std::vector<std::string>;
	while ((start = str.find_first_not_of(delimiter, end)) != std::string::npos) // find_first_not_of-> Searches the string for the first character that does not match any of the characters specified in its arguments. // npos->
	{
		end = str.find(delimiter, start);                                       // find -> Return the position of the first character of the first match, or ::npos if match nothing.
		out->push_back(str.substr(start, end - start));                         // add to vector container the substring from start to delimiter and from delimiter to the end
	}
	return (out);
}

std::string	itos(int n)
{
	std::ostringstream s;

	s << n;
	return (s.str());
}

void	print_log(std::string file_name, std::string status, int type)
{
	time_t				now = time(0);;
	tm 					*ltm = localtime(&now);
	std::ostringstream	msg;
	std::fstream		logfile;

	logfile.open("log", std::ios::app);
	if (type == 1)
	{
		msg << 1900 + ltm->tm_year << "/" << 1 + ltm->tm_mon << "/" << 1 + ltm->tm_mday;
		msg << " ";
		msg	<< ltm->tm_hour << ":" << ltm->tm_min << ":" << ltm->tm_sec;
		msg << " (";
		msg << file_name;
		msg << ") : ";
		msg << status;
		std::cout << YELLOW << msg.str() << RESET_COLOR << std::endl;
	}
	else if (type == 0)
	{
		if (status.length() > 0)
		{
			msg << "----------------------------------------------------------------------------------" << std::endl;
			msg << status;
			msg << "\n----------------------------------------------------------------------------------" << std::endl;
			std::cout << msg.str().substr(0, 900) << std::endl;
			if (msg.str().length() >= 900)
				std::cout << "----------------------------------------------------------------------------------" << std::endl;
		}
	}
	logfile << msg.str() << std::endl;
}
