#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include <StatusLine.hpp>
#include <Utils.hpp>

class Response
{
private:
	StatusLine		_statusLine;
	std::string		_contentType;
	std::string		_contentLength;
	std::string		_lastModified;
	std::string		_header;
	std::string		_body;
	std::string		_str;

public:
	//occf
	Response(void);
	~Response(void);

	//getters & setters
	void			setContentType(std::string contentType);
	std::string		getContentType(void);
	void			setContentLength(std::string contentLength);
	std::string		getContentLength(void);
	void			setLastModified(std::string lastModified);
	std::string		getLastModified(void);
	void			setHeader(std::string header);
	std::string		getHeader(void);
	void			setBody(std::string body);
	std::string		getBody(void);
	void			setStatusLine(StatusLine statusLine);
	StatusLine		getStatusLine(void);
	std::string		toString(void);
	const char		*toCString(void);
	StatusLine		statusLineProcessor(void);
};

#endif
