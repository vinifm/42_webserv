#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include <iostream>
#include <fstream>
#include <StatusLine.hpp>

class Response
{
private:
	std::string					_contentType;
	int							_contentLength;
	std::string					_lastModified;
	std::string					_header;
	std::string					_body;
	std::string					_str;
	std::map<int, std::string>	_http_codes;

public:
	StatusLine					*_statusLine;
	//occf
	Response(std::map<int, std::string> http_codes);
	~Response(void);

	//methods
	std::string		buildHeader(void);
	std::string		buildResponse(void);

	//getters & setters
	void			setContentType(std::string contentType);
	std::string		getContentType(void);
	void			setContentLength(int contentLength);
	int				getContentLength(void);
	void			setLastModified(std::string lastModified);
	std::string		getLastModified(void);
	void			setBody(std::string body);
	std::string		getBody(void);
	std::string		toString(void);
	void			setHeader(std::string header);
	std::string		getHeader(void);
	const char		*toCString(void);
};

#endif
