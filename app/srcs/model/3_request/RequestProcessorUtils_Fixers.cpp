#include <Request.hpp>

std::string	fix_route(std::string route, Location *location)
{
	(void) location;
	if (route == "")
		route.append("index.html");
	return (route);
}

Location	*set_last_root(Parser &parser, std::string& _last_root, std::string& route)
{
	std::vector<std::string>	*route_split = ft_split(route, '/');
	std::vector<std::string>	split = (*route_split);
	Location *fake_location = new Location("/", parser.getRoot(), false);
	if (split.size() <= 0)
	{
		if (route == "")
			_last_root = parser.getRoot();
		return (fake_location);
	}
	// SERÁ QUE É UMA ROTA VÁLIDA E PRECISA MUDAR O SITE?
	std::string	first = split[0];
	Location *location = is_valid_location(std::string("/").append(first), parser);
	if (location && split.size() >= 1)
	{
		std::string find = (*location)._route;
		find = del_start_bar(find);
		route = route.replace(route.find(find), find.length(), "");
		route = del_start_bar(route);
	}
	if (location && split.size() >= 1)
	{
		if (_last_root.find((*location)._root) == std::string::npos)
			_last_root = (*location)._root;
		std::ostringstream ss;
		ss << _last_root << route;
		return (location);
	}
	return (fake_location);
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

std::string	del_start_bar(std::string root)
{
	if (root.empty())
		return (root);
	else
	{
		if (root[0] == '/')
			root = root.substr(1, root.length());
	}
	return (root);
}

