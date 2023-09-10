#include <Request.hpp>

int	can_execute(std::string path)
{
	if (access(path.c_str(), X_OK) == 0)
		return (1);
	return (0);
}

int	can_read(std::string path)
{
	if (access(path.c_str(), R_OK) == 0)
		return (1);
	return (0);
}

int	file_exist(std::string path)
{
	if (access(path.c_str(), F_OK) == 0)
		return (1);
	return (0);
}

int	is_directory(std::string path)
{
	struct stat	path_stat;

	if (stat(path.c_str(), &path_stat) != 0)
		return (0);
	if (S_ISDIR(path_stat.st_mode))
		return (1);
	return (0);
}
