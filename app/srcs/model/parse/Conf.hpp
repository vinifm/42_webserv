#ifndef CONF_HPP
#define CONF_HPP

#include <Utils.hpp>

class Conf
{
private:
	std::string	_root;
	int			_port;

public:
	//occf
	Conf(void);
	~Conf(void);
	Conf(std::string path);

	//methods
	int				is_valid(void);

	//getters && setters
	int				getPort(void);
	void			setPort(int port);
	std::string		getRoot(void);
	void			setRoot(std::string root);

};

#endif