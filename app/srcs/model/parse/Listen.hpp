#ifndef LISTEN_HPP
# define LISTEN_HPP

#include <iostream>
#include <sstream>
#include <vector>

class Listen
{
public:
	Listen();
	~Listen();

	void	initListen(std::stringstream& values);

private:
	std::string	_address;
	int			_port;

	void	_setPort(const std::string& port);

};

#endif

