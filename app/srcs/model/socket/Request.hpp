#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <Utils.hpp>

class Request
{
private:
	std::string	_str;
	std::string	_route;
	std::string	_method;

public:
	//occf
	Request(void);
	~Request(void);
	Request(std::string request_str);

	//methods
	void		extract(void);
	int			executeRequest(void);

	//getters & setters
	std::string	toString(void);
	void		setStr(std::string str);
	std::string	getRoute(void);
	void		setRoute(std::string route);
	std::string	getMethod(void);
	void		setMethod(std::string method);

};

#endif
