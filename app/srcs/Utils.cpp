#include <Utils.hpp>

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

void	print_list(std::string title, std::vector<std::string> *list)
{
	std::vector<std::string>::iterator	it;

	std::cout << title << std::endl;
	for (it = list->begin(); it < list->end(); it++)
	{
		std::cout << *it << std::endl;
	}
}
