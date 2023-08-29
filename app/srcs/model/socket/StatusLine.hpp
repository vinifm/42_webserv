#ifndef STATUSLINE_HPP
#define STATUSLINE_HPP

#include <Utils.hpp>

class StatusLine
{
private:
	std::string						_protocol;
	std::map<int, std::string>		_code;
	std::string						_result;

public:
	//occf
	StatusLine(void);
	~StatusLine(void);

	//getters & setters
	std::string		getProtocol(void);
	void			setProtocol(std::string protocol);
	std::string		getResult(void);
	void			setResult(std::string result);
	int				getCode(void);
	std::string		getCodeMessage(void);
	void			setCode(std::map<int, std::string> code);
	std::string		toString(void);

};
#endif
