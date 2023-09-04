#include "Parser.hpp"

Parser::Parser() : _isValid(false) {}
Parser::~Parser() {}

static std::string trim(const std::string& line)
{
	std::string trimmed = line;

	size_t start = trimmed.find_first_not_of(" \t");
	if (start != std::string::npos) {
		trimmed = trimmed.substr(start);
	}

	size_t end = trimmed.find_last_not_of(" \t");
	if (end != std::string::npos) {
		trimmed = trimmed.substr(0, end + 1);
	}
	return trimmed;
}

void	Parser::parseConfigFile(const std::string filename)
{
	_inputFile.open(filename.c_str(), std::ifstream::in);
	if (_checkFileExtension(filename) == false) {
		std::cerr << "Error: not a .conf file" << std::endl;
		return ;
	}
	else if (!_inputFile.is_open())
	{
		std::cerr << "Error: could not open config file" << std::endl;
		return ;
	}
	while (std::getline(_inputFile, _line)) {
		_line = trim(_line);
		if (_line.compare("server {") == 0) {
			_addServer();
		}
	}
	_inputFile.close();
}

/* Return true if file ends with '.conf' */
bool	Parser::_checkFileExtension(const std::string& filename) const
{
	size_t		dot_position = filename.find_last_of(".");
	std::string	filename_extension;

	if (dot_position == std::string::npos)
		return false;
	filename_extension = filename.substr(dot_position);
	if (filename_extension.compare(".conf") == 0)
		return true;
	return false;
}

void	Parser::_addServer()
{
	Server server;
	server.initServer(_inputFile);
	// _server.push_back(server);
}

/* Print all servers info */
std::ostream& operator<<(std::ostream& os, const Parser& parser)
{
	for (size_t i = 0; i < parser.getServerSize(); ++i)
		std::cout << parser.getServer(i) << std::endl;
}

/*--- GETTERS ----------------------------------------------------------------*/

bool	Parser::getIsValid() const { return _isValid; }
Server	Parser::getServer(size_t index) const { return _servers.at(index); }
size_t	Parser::getServerSize() const {return _servers.size(); }
