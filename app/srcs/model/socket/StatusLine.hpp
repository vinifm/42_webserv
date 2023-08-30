#ifndef STATUSLINE_HPP
#define STATUSLINE_HPP

#include <Webserv.hpp>

class StatusLine
{
private:
	std::string									_protocol;
	std::map<int, std::string>::iterator		_code;
	std::string									_result;

public:
	//occf
	StatusLine(void);
	~StatusLine(void);
	StatusLine(std::string protocol, std::map<int, std::string>::iterator code, std::string result);

	//getters & setters
	std::string		getProtocol(void);
	void			setProtocol(std::string protocol);
	std::string		getResult(void);
	void			setResult(std::string result);
	int				getCode(void);
	std::string		getCodeMessage(void);
	void			setCode(std::map<int, std::string>::iterator code);
	std::string		toString(void);

};
#endif
