#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include <iostream>
#include <fstream>
#include <StatusLine.hpp>

class Response
{
private:
	StatusLine		_statusLine;
	std::string		_contentType;
	int				_contentLength;
	std::string		_lastModified;
	std::string		_header;
	std::string		_body;
	std::string		_str;
	int				_length;

public:
	//occf
	Response(void);
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
	void			setStatusLine(StatusLine statusLine);
	StatusLine		getStatusLine(void);
	std::string		toString(void);
	void			setHeader(std::string header);
	std::string		getHeader(void);
	const char		*toCString(void);
	StatusLine		statusLineProcessor(void);
	int				getLength(void);
	void			setLength(int length);
};

//exception
void			init_http_codes(std::map<int, std::string>& http_codes);
std::string		error_404(Response &response);
std::string		error_403(Response &response);

#endif
