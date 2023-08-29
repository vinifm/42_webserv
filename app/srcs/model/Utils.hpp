#ifndef UTILS_HPP
#define UTILS_HPP

//general utils libs
#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <unistd.h>
#include <sstream>

//socket libs
#include <sys/socket.h>
#include <netinet/in.h>

//file stream libs
#include <fstream>

//containers
#include <vector>

//webserv
#include <ConfFile.hpp>
#include <Request.hpp>
#include <Socket.hpp>
#include <Response.hpp>

//colors
# define BLACK "\033[0;30m"
# define BOLD_BLACK "\033[1;30m"
# define RED "\033[0;31m"
# define BOLD_RED "\033[1;31m"
# define GREEN "\033[0;32m"
# define BOLD_GREEN "\033[1;32m"
# define YELLOW "\033[0;33m"
# define BOLD_YELLOW "\033[1;33m"
# define BLUE "\033[0;34m"
# define BOLD_BLUE "\033[1;34m"
# define PURPLE "\033[0;35m"
# define BOLD_PURPLE "\033[1;35m"
# define CYAN "\033[0;36m"
# define BOLD_CYAN "\033[1;36m"
# define WHITE "\033[0;37m"
# define BOLD_WHITE "\033[1;37m"
# define RESET_COLOR "\033[0m"

//********************
//                   *
//    PROTOTYPES     *
//                   *
//********************
std::vector<std::string>	*ft_split(std::string str, char delimiter);
void						print_log(std::string file_name, std::string message);
void                        print_banner(void);
std::string					itos(int n);

//********************
//                   *
//     AUXILIARY     *
//     VARIABLES     *
//                   *
//********************
// enum
// {
// 	CODE_200="OK",
// 	CODE_201="Created",
// 	CODE_202="Accepted",
// 	CODE_204="No Content",
// 	CODE_300="Multiple Choice",
// 	CODE_301="Moved Permanently",
// 	CODE_302="Found",
// 	CODE_400="Bad Request",
// 	CODE_401="Unauthorized",
// 	CODE_403="Forbidden",
// 	CODE_404="Not Found",
// 	CODE_413="Method Not Allowed",
// 	CODE_415="Request Entity Too Large",
// 	CODE_500="Unsupported Media Type",
// 	CODE_502="Bad Gateway",
// 	CODE_504="Gateway Timeout",
// 	CODE_505="HTTP Version Not Supported"
// };

#endif
