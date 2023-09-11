#include "ErrorPages.hpp"

ErrorPages::ErrorPages() {}
ErrorPages::~ErrorPages() {}

void ErrorPages::addPages(std::stringstream& values)
{
	std::stringstream	ss_copy(values.str());
	std::string			path;
	std::string			error_code;
	while (ss_copy >> path)
		continue ;
	while (values >> error_code)
		_pages[error_code] = path;
	_pages.erase(path);
}

/*--- GETTERS ----------------------------------------------------------------*/

std::string ErrorPages::getPath(std::string error_code) const {
	return _pages.at(error_code);
}

std::map<std::string, std::string>	ErrorPages::getErrorPagesMap() const {
	return _pages;
}

/*--- INSERTION OVERLOAD -----------------------------------------------------*/

std::ostream& operator<<(std::ostream& os, const ErrorPages& ep)
{
	std::map<std::string, std::string>	pages = ep.getErrorPagesMap();
	os << "Error Pages:" << std::endl;
	std::map<std::string, std::string>::iterator it;
	for (it = pages.begin(); it != pages.end(); ++it) {
		os << "\tCode: " << it->first
			<< ", Path: " << it->second
			<< std::endl;
	}
	return os;
}
