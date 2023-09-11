#ifndef LOCATION_HPP
# define LOCATION_HPP

#include <includes.hpp>
#include <ErrorPages.hpp>

class Location
{
public:
	Location();
	~Location();
	Location&	operator=(const Location& rhs);
	Location(const Location& copy);

	std::vector<std::string>::iterator&	initLocation(std::vector<std::string>& inputFile, std::string prefix,
		std::vector<std::string>::iterator& line);

	std::string	getPrefix() const;
	std::string	getRoot() const;
	std::string	getIndex(size_t index) const;
	std::vector<std::string>	getIndex() const;
	size_t		getIndexSize() const;
	bool		getAutoindex() const;
	std::string	getLimitExcept(size_t index) const;
	size_t		getLimitExceptSize() const;
	std::string	getRedirect() const;

private:
	std::string					_prefix;
	std::string					_root;
	std::vector<std::string>	_index;
	bool						_autoindex;
	std::vector<std::string>	_limit_except;
	std::string					_redirect;

	void	_setRoot(std::stringstream& ss);
	void	_setLimitExcept(std::stringstream& ss);
	void	_setIndex(std::stringstream& ss);
	void	_setAutoindex(std::stringstream& ss);
	void	_setRedirect(std::stringstream& ss);
	void	_setCGI(std::stringstream& ss);
};

std::ostream& operator<<(std::ostream& os, const Location loc);

#endif

