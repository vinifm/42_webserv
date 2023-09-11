#include <Request.hpp>

std::string	fix_route(std::string route, Location *location)
{
	(void) location;
	if (route == "")
		route.append("index.html");
	return (route);
}

int	set_last_root(Parser &parser, std::string& _last_root, std::string& route)
{
	std::vector<std::string>	*route_split = ft_split(route, '/');
	std::vector<std::string>	split = (*route_split);

	if (split.size() <= 0)
	{
		_last_root = parser.getServer(0).getRoot();
		if (parser.getServer(0).getLocation(0).getPrefix() == "/")
			_last_root = parser.getServer(0).getLocation(0).getRoot();
		return (-1);
	}
	else
	{
		std::string	requisition_route_prefix = split[0];
		std::string	create_prefix_similar_to_conf_file = std::string("/").append(requisition_route_prefix);
		print_log("", create_prefix_similar_to_conf_file, 0);
		int location_index = is_valid_location(create_prefix_similar_to_conf_file, parser);
		if (location_index != -1 && split.size() >= 1)
		{
			//remove location prefix from requisition route
			std::string find = parser.getServer(0).getLocation(location_index). getPrefix();
			find = del_start_bar(find);
			route = route.erase(0, find.length());
			print_log("", route, 0);
			route = del_start_bar(route);

			//if, root do location for diferente do root anterior, troca
			if (_last_root.find(parser.getServer(0).getLocation(location_index).getRoot()) == std::string::npos)
				_last_root = parser.getServer(0).getLocation(location_index).getRoot();

			return (location_index);
		}
	}
	return (-1);
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

