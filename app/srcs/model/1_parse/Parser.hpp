#ifndef PARSER_HPP
# define PARSER_HPP

#include <includes.hpp>
#include <Server.hpp>
#include <pallete.hpp>

class Parser
{
public:
	Parser();
	Parser&	operator=(const Parser& rhs);
	Parser(const Parser& copy);
	~Parser();

	void	parseConfigFile(const std::string filename);
	std::vector<Server> getServers() const;
	Server	getServer(size_t index) const;
	size_t	getServerSize() const;
	std::vector<std::string>	getInputFile() const;
	std::vector<std::string>::iterator getLine() const;

private:
	std::vector<Server>			_servers;
	std::vector<std::string>	_inputFile;
	std::vector<std::string>::iterator _line;

	bool	_checkFileExtension(const std::string& filename) const;
	void	_addServer();
};

std::ostream& operator<<(std::ostream& os, const Parser& parser);

//utils
void						print_log(std::string file_name, std::string status, int type);
std::vector<std::string>	*ft_split(std::string str, char delimiter);

#endif
