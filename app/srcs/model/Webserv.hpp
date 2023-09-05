#ifndef WEBSERV_HPP
#define WEBSERV_HPP

//general Webserv libs
#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <sstream>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>

//socket libs
#include <sys/socket.h>
#include <netinet/in.h>

//file stream libs
#include <fstream>

//containers
#include <vector>
#include <map>

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
extern std::map <int, std::string> *g_http_codes;

#endif
