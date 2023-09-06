#ifndef PARSER_HPP
# define PARSER_HPP

#include "includes.hpp"
#include "Server.hpp"

class Parser
{
public:
	Parser();
	~Parser();

	void	parseConfigFile(const std::string filename);

	bool	getIsValid() const;
	Server	getServer(size_t index) const;
	size_t	getServerSize() const;

private:
	std::vector<Server>			_servers;
	bool						_isValid;
	std::vector<std::string>	_inputFile;
	std::vector<std::string>::iterator _line;

	bool	_checkFileExtension(const std::string& filename) const;
	void	_addServer();
};

std::ostream& operator<<(std::ostream& os, const Parser& parser);

#endif
