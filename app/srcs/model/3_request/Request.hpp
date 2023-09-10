#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <Parser.hpp>
#include <Response.hpp>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>
#include <bits/stdc++.h>
#include <cstdio>
#include <iostream>
#include <algorithm>

#define AWS "./srcs/view/www/aws/"

class Request
{
private:
	std::string		_str;
	std::string		_route;
	std::string		_method;
	std::string		_type;
	std::string		_upload_file_name;
	std::string		_header;
	std::string		_body;
	static std::string			_last_root;

public:
	std::map<int, std::string>	http_codes;

	//occf
	Request(void);
	~Request(void);
	Request(std::string request_str);

	//getters & setters
	std::string								toString(void);
	void									setStr(std::string str);
	std::string								getUploadFileName(void);
	void									setUploadFileName(std::string upload_file_name);
	std::string								getRoute(void);
	void									setRoute(std::string route);
	std::string								getMethod(void);
	void									setMethod(std::string method);
	std::string								getType(void);
	void									setType(std::string type);
	std::string								getHeader(void);
	void									setHeader(std::string header);
	std::string								getBody(void);
	void									setBody(std::string body);
	std::string								getLastRoot(void);
	void									setLastRoot(std::string last_root);

	//methods
	int			executeRequest(Parser parser, Response& response);
	void		setResponseBody(Parser& parser, Response& response);
	void		setResponseHeader(Response& response);
	std::string	execute_get(Parser& parser, Response& response);
	std::string	execute_post(Response& response);
	std::string	execute_delete(Response& response);
};

//extractors
std::string		extract_method(std::string request);
std::string		extract_route(std::string request);
std::string		extract_body(std::string request);
std::string		extract_header(std::string request);
std::string		extract_file_name(std::string request);
std::string		extract_just_file_content(std::string body);
std::string		extract_delete_file_name(std::string delete_body);
//fixes
std::string		add_final_bar(std::string root);
std::string		del_final_bar(std::string root);
std::string		del_start_bar(std::string root);
Location		*set_last_root(Parser &parser, std::string& _last_root, std::string& route);
std::string		fix_route(std::string route, Location *location);
//access
int				can_execute(std::string path);
int				can_read(std::string path);
int				file_exist(std::string path);
int				is_directory(std::string path);
//buffer generators
std::string		load_file_bytes_in_body(std::string path);
std::string		generate_autoindex(std::string path);
std::string		serve_route(std::string& route, Location *location, Request& request, Response& response);
//validators
std::string		find_index_in_directory(std::vector<std::string> index, std::string path);
Location		*is_valid_location(std::string first, Parser& parser);
//cgi
void			execute_scripts(Request &request, Response &response);
//http status
void			init_http_codes(std::map<int, std::string>& http_codes);
std::string		error_404(Request& request, Response &response);
std::string		error_403(Request& request, Response &response);
#endif
