#ifndef PARSER_HPP
# define PARSER_HPP

#include "Server.hpp"

class Parser
{
public:
	Parser();
	~Parser();

private:
	std::vector<Server>	_servers;
};

#endif
