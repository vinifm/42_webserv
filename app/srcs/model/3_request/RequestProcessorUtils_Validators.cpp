#include <Request.hpp>

int is_valid_location(std::string prefix, Parser parser) // check if passed route exist in some location on Parser class;
{
	int	i = 0;
	std::vector<Location> locations = parser.getServer(0).getLocations();
	for (std::vector<Location>::iterator it = locations.begin(); it < locations.end(); it++)
	{
		if (prefix == it->getPrefix())
			return (i);
		i++;
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
