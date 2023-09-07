#include <Request.hpp>

std::string	fix_route(Parser& parser, std::string route)
{
	if (route == "/" || route == "")
	{
		route = "./";
		route = route.append(parser.getRoot());
		add_final_bar(route);
	}
 	if (route[0] == '/')
	{
		route = del_final_bar(parser.getRoot()).append(route);
	}
	return (route);
}

std::string	add_final_bar(std::string root)
{
	if (root.empty())
		return (root);
	else
	{
		if (root[root.length() - 1] != '/')
			root.append("/");
	}
	return (root);
}

std::string	del_final_bar(std::string root)
{
	if (root.empty())
		return (root);
	else
	{
		if (root[root.length() - 1] == '/')
			root = root.substr(0, root.length() - 1);
	}
	return (root);
}

