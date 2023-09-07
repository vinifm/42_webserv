#include "Location.hpp"

Location::Location() : _autoindex(false) {}
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
		if (directive == "#")
			continue;
		else if (directive == "root")
			_setRoot(ss);
		else if (directive == "index")
			_setIndex(ss);
		else if (directive == "limit_except")
			_setLimitExcept(ss);
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

/*--- SETTERS ----------------------------------------------------------------*/

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
	std::string path;
	if (!(ss >> path))
		throw std::runtime_error("Missing redirect path");
	_redirect = path;
}

void	Location::_setCGI(std::stringstream& ss)
{
	(void)ss;
}

/*--- GETTERS ----------------------------------------------------------------*/

std::string	Location::getPrefix() const { return _prefix; }
std::string	Location::getRoot() const { return _root; }
std::string	Location::getIndex(size_t index) const { return _index.at(index); }
size_t		Location::getIndexSize() const { return _index.size(); }
bool		Location::getAutoindex() const { return _autoindex; }
std::string	Location::getLimitExcept(size_t index) const { return _limit_except.at(index); }
size_t		Location::getLimitExceptSize() const { return _limit_except.size(); }
std::string	Location::getRedirect() const { return _redirect; }

/*--- INSERTION OVERLOAD -----------------------------------------------------*/

std::ostream& operator<<(std::ostream& os, const Location loc)
{
	os << "prefix: " << loc.getPrefix() << std::endl;
	if (loc.getRoot() != "")
		os << "root: " << loc.getRoot() << std::endl;

	if (loc.getIndexSize() != 0) {
		os << "index: " << std::endl;
		for (size_t i = 0; i < loc.getIndexSize(); ++i)
			os << "\t" << loc.getIndex(i) << std::endl;
	}

	os << "autoindex: " << loc.getAutoindex() << std::endl;

	if (loc.getLimitExceptSize() != 0) {
		os << "limit_except:" << std::endl;
		for (size_t i = 0; i < loc.getLimitExceptSize(); ++i)
			os << "\t" << loc.getLimitExcept(i) << std::endl;
	}

	if (loc.getRedirect() != "")
		os << "redirect: " << loc.getRedirect() << std::endl;
	return os;
}
