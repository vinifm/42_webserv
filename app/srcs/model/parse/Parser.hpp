#ifndef PARSER_HPP
# define PARSER_HPP

#include "Server.hpp"
#include <fstream>
#include <sstream>

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
	std::vector<Server>	_servers;
	bool				_isValid;
	std::ifstream		_inputFile;
	std::string			_line;

	bool	_checkFileExtension(const std::string& filename) const;
	void	_addServer();
};

std::ostream& operator<<(std::ostream& os, const Parser& parser);

#endif
