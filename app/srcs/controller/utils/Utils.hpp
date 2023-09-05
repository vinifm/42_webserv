#ifndef UTILS_HPP
#define UTILS_HPP

#include <Webserv.hpp>

int	can_execute(std::string path);
int	can_read(std::string path);
int	file_exist(std::string path);
int	is_directory(std::string path);

#endif