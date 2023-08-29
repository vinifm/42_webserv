#include <Utils.hpp>

// USED TO SPLIT THE URI AND EXTRAT DOMAIN, PORT AND ROUTE (http://|localhost:|80/|blabla);
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

// PRINT MESSAGE WITH CURRENT DATE AND HOUR
void	print_log(std::string file_name, std::string status)
{
	time_t				now = time(0);;
	tm 					*ltm = localtime(&now);
	std::ostringstream	msg;

	// build message to print
	msg << 1900 + ltm->tm_year << "/" << 1 + ltm->tm_mon << "/" << 1 + ltm->tm_mday;
	msg << " ";
	msg	<< ltm->tm_hour << ":" << ltm->tm_min << ":" << ltm->tm_sec;
	msg << " [ ";
	msg << file_name;
	msg << " ] : ";
	msg << status;
	std::cout << BOLD_YELLOW << msg.str() << RESET_COLOR << std::endl;
}

// PRINT INITIAL BANNER
void	print_banner(void)
{
	std::string		path;
	std::fstream	file;
	std::string		line;

	path = ".banner";
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

// CONVERTERS

// int to std::string
std::string	itos(int n)
{
	std::ostringstream s;

	s << n;
	return (s.str());
}
