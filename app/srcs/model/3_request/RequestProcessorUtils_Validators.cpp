#include <Request.hpp>

int	is_valid_location(std::string route, Parser& parser) // check if passed route exist in some location on Parser class;
{
	int	index_location = 0;

	for (std::vector<Location>::iterator it = parser._location.begin(); it < parser._location.end(); it++)
	{
		if (route == it->_route)
			return (index_location);
		index_location++;
	}
	return (-1);
}

std::string find_index_in_directory(std::vector<std::string> index, std::string path)
{
	/*
		1) LOOP THE DIRECTORY LIST OF FILES TRYING TO FIND SOME STRING INSIDE INDEX;
	*/
	DIR				*directory = opendir(path.c_str());
	struct dirent	*file;

	while ((file = readdir(directory)) != NULL)
	{
		for (std::vector<std::string>::iterator it = index.begin(); it < index.end(); it++)
		{
			if (std::string(file->d_name) == *it)
			{
				closedir(directory);
				return (*it);
			}
		}
	}
	closedir(directory);
	return ("");
}
