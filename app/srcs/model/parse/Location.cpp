#include "Location.hpp"

Location::Location() {}
Location::~Location() {}

std::vector<std::string>::iterator&	Location::initLocation(std::vector<std::string>& inputFile, std::string prefix,
	std::vector<std::string>::iterator& line)
{
	std::string	directive;

	_prefix = prefix;
	for (; line != inputFile.end(); ++line) {
		std::stringstream ss(*line);
		if (!(ss >> directive))
			continue;
		std::cout << "\t\tloc directive: " << directive << std::endl;
		if (directive == "#")
			continue;
		else if (directive == "root")
			_setRoot(ss);
		else if (directive == "index")
			_setIndex(ss);
		else if (directive == "limit_except")
			_setLimitExcept(ss);
		else if (directive == "client_max_body_size")
			_setClientSize(ss);
		else if (directive == "autoindex")
			_setAutoindex(ss);
		else if (directive == "redirect")
			_setRedirect(ss);
		else if (directive == "cgi")
			_setCGI(ss);
		else if (directive == "}")
			return line;
		else {
			std::cout << "Directive: " << directive << std::endl;
			throw std::runtime_error("invalid location directive");
		}
		directive = "\0";
	}
	throw std::runtime_error("unclosed server block");
}
void	Location::_setRoot(std::stringstream& ss)
{
	std::string	root_path;
	if (!(ss >> root_path))
		throw std::runtime_error("Missing location root path");
	_root = root_path;
}
void	Location::_setIndex(std::stringstream& ss)
{
	std::string	file;
	while (ss >> file)
		_index.push_back(file);
}
void	Location::_setLimitExcept(std::stringstream& ss)
{
	std::string	method;
	while (ss >> method)
		_limit_except.push_back(method);
}
void	Location::_setClientSize(std::stringstream& ss)
{
	std::string	client_size;
	if (!(ss >> client_size))
		throw std::runtime_error("Missing client max body size option");
	_client_max_body_size = client_size;
}
void	Location::_setAutoindex(std::stringstream& ss)
{
	std::string autoindex_option;
	ss >> autoindex_option;
	if (autoindex_option == "on")
		_autoindex = true;
	else if (autoindex_option == "off")
		_autoindex = false;
	else
		throw std::runtime_error("Invalid autoindex option");
}
void	Location::_setRedirect(std::stringstream& ss)
{
	(void)ss;
}
void	Location::_setCGI(std::stringstream& ss)
{
	(void)ss;
}
