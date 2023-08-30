#ifndef Parser_HPP
#define Parser_HPP

#include <Webserv.hpp>

class Parser
{
private:
	std::string	_root;
	int			_port;

public:
	//occf
	Parser(void);
	~Parser(void);
	Parser(std::string path);

	//methods
	int				is_valid(void);

	//getters && setters
	int				getPort(void);
	void			setPort(int port);
	std::string		getRoot(void);
	void			setRoot(std::string root);

};

#endif