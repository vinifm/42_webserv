#include <Request.hpp>

Location *is_valid_location(std::string first, Parser& parser) // check if passed route exist in some location on Parser class;
{
	for (std::vector<Location>::iterator it = parser._location.begin(); it < parser._location.end(); it++)
	{
		if (first == it->_route)
			return (&(*it));
	}
	return (NULL);
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
