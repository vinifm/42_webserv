#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <Utils.hpp>
#include <Parser.hpp>
#include <Response.hpp>
#include <Webserv.hpp>

class Request
{
private:
	std::string	_str;
	std::string	_route;
	std::string	_method;
	std::string	_type;

public:
	//occf
	Request(void);
	~Request(void);
	Request(std::string request_str);

	//methods
	void	extract(void);
	int		executeRequest(Parser parser, Response& response);
	void	setResponseHeader(Response& response);
	void	setResponseBody(std::string path, Response& response);

	//getters & setters
	std::string	toString(void);
	void		setStr(std::string str);
	std::string	getRoute(void);
	void		setRoute(std::string route);
	std::string	getMethod(void);
	void		setMethod(std::string method);
	std::string	getType(void);
	void		setType(std::string type);

};

	//utils
	std::string		generate_autoindex(std::string path);
	std::string		extract_route(std::string url);
	std::string		extract_method(std::string url);
	std::string		load_file_bytes_in_body(std::string path);

	//errors
	void			error_404(Response &response);
	void			error_403(Response &response);


#endif
