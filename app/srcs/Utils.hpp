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
void						print_list(std::string title, std::vector<std::string> *list);

#endif
