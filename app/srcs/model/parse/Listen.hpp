#ifndef LISTEN_HPP
# define LISTEN_HPP

#include <iostream>
#include <vector>

class Listen
{
public:
	Listen();
	~Listen();

private:
	std::string	_address;
	int			_port;
};

#endif

