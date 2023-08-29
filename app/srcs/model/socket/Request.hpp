#ifndef REQUEST_HPP
#define REQUEST_HPP

class Request
{
private:
	char		_str[1024];
	std::string	_route;
	std::string	_method;

public:
	//occf
	Request(void);
	~Request(void);
	Request(std::string request_str);

	//methods

	//getters & setters
	std::string	getStr(void);
	void		setStr(std::string str);
	std::string	getRoute(void);
	void		setRoute(std::string route);
	std::string	getMethod(void);
	void		setMethod(std::string method);

};

#endif