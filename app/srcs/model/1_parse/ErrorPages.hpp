#ifndef ERROR_PAGES_HPP
# define ERROR_PAGES_HPP

#include <includes.hpp>

class ErrorPages
{
public:
	ErrorPages();
	~ErrorPages();

	void		addPages(std::stringstream& values);
	std::string	getPath(std::string error_code) const;
	std::map<std::string, std::string>	getErrorPagesMap() const;

private:
	std::map<std::string, std::string>	_pages;
};

std::ostream& operator<<(std::ostream& os, const ErrorPages& ep);

#endif
