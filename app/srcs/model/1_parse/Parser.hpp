#ifndef PARSER_HPP
#define PARSER_HPP

#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <pallete.hpp>

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
	std::string					_root;
	int							_port;

public:
	std::vector<std::string>	_index;
	std::vector<Location> 		_location;
	bool						_autoindex;
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

	void						init_parser_for_test(Parser& parser);
	std::vector<std::string>	*ft_split(std::string str, char delimiter);
	std::string					itos(int n);
	void						print_log(std::string file_name, std::string status, int type);

#endif