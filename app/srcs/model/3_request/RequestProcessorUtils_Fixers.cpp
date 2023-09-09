#include <Request.hpp>



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

