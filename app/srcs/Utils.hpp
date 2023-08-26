#ifndef UTILS_HPP
#define UTILS_HPP

//general utils libs
#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <unistd.h>

//socket libs
#include <sys/socket.h>
#include <netinet/in.h>

//file stream libs
#include <fstream>
#include <sstream>

//containers
#include <vector>

//webserv
#include <Socket.hpp>

//*******************
//                  *
//    PROTOTYPE     *
//                  *
//*******************
std::vector<std::string>	*ft_split(std::string str, char delimiter);
void						print_log(std::string file_name, std::string message);
void						print_banner(void);
std::string	                itos(int n);

#endif
