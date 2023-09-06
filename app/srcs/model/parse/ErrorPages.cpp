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

	// std::map<std::string, std::string>::iterator it;
    // for (it = _pages.begin(); it != _pages.end(); ++it) {
    //     std::cout << "Key: " << it->first << ", Value: " << it->second << std::endl;
    // }
}
