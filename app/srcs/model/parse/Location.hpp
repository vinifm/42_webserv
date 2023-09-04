#ifndef LOCATION_HPP
# define LOCATION_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "ErrorPages.hpp"

class Location
{
public:
	Location();
	~Location();

	std::vector<std::string>::iterator&	initLocation(std::vector<std::string>& inputFile, std::string prefix,
		std::vector<std::string>::iterator& line);

private:
	std::string					_prefix;
	std::string					_root;
	std::vector<std::string>	_index;
	ErrorPages					_error_pages;
	bool						_autoindex;
	std::string					_client_max_body_size;
	std::vector<std::string>	_limit_except;
	std::string					_redirect;

	void	_setRoot(std::stringstream& ss);
	void	_setIndex(std::stringstream& ss);
	void	_setErrorPage();
	void	_setLimitExcept(std::stringstream& ss);
	void	_setClientSize(std::stringstream& ss);
	void	_setAutoindex(std::stringstream& ss);
	void	_setRedirect(std::stringstream& ss);
	void	_setCGI(std::stringstream& ss);
};

#endif

