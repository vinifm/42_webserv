#ifndef Parser_HPP
#define Parser_HPP

#include <Webserv.hpp>

class Location
{
	public:
	std::string					_root;
	std::string					_route;
	bool						_autoindex;
	std::vector<std::string>	_index;

	Location(std::string route, std::string root, bool autoindex)
	{
		this->_route = route;
		this->_root = root;
		this->_autoindex = autoindex;
		this->_index.push_back("index.html");
		this->_index.push_back("index.php");
	}
};

class Parser
{
private:
	std::string	_root;
	int			_port;

public:
	std::vector<Location> _location;
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