#ifndef LISTEN_HPP
# define LISTEN_HPP

#include <includes.hpp>

class Listen
{
public:
	Listen();
	~Listen();

	void	initListen(std::stringstream& values);

	std::string	getAddress() const;
	int			getPort() const;

private:
	std::string	_address;
	int			_port;

	void	_setPort(const std::string& port);

};

std::ostream& operator<<(std::ostream& os, const Listen& listen);

#endif

