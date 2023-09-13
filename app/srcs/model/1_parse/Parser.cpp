#include <Parser.hpp>

Parser::Parser() {}
Parser::~Parser() {}
Parser::Parser(const Parser& copy) { *this = copy; }
Parser&	Parser::operator=(const Parser& rhs) {
	if (this != &rhs) {
		_servers = rhs.getServers();
		_inputFile = rhs.getInputFile();
		_line = rhs.getLine();
	}
	return *this;
}

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
	std::ifstream	file_stream;
	std::string		file_line;

	file_stream.open(filename.c_str(), std::ifstream::in);
	if (_checkFileExtension(filename) == false) {
		std::cerr << BOLD_RED << "ERROR: " << RESET_COLOR
			<< "not a .conf file" << std::endl;
		return ;
	}
	else if (!file_stream.is_open())
	{
		std::cerr << BOLD_RED << "ERROR: " << RESET_COLOR
			<< "could not open .conf file" << std::endl;
		return ;
	}
	while (std::getline(file_stream, file_line)) {
		file_line = trim(file_line);
		_inputFile.push_back(file_line);
	}
	file_stream.close();
	for (_line = _inputFile.begin(); _line != _inputFile.end(); ++_line) {
		if (*_line == "" || (*_line)[0] == '#')
			continue;
		if (*_line++ == "server {")
			_addServer();
	}
	if (getServerSize() == 0)
		throw std::runtime_error("parsing failed: no servers added");
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
	_line = server.initServer(_inputFile, _line);
	if (server.getRoot() == "")
		throw std::runtime_error("server block: missing root");
	if (server.getIndexSize() == 0)
		throw std::runtime_error("server block: missing index");
	_servers.push_back(server);
}

/*--- GETTERS ----------------------------------------------------------------*/
std::vector<Server> Parser::getServers() const { return _servers; };
Server	Parser::getServer(size_t index) const { return _servers.at(index); }
size_t	Parser::getServerSize() const { return _servers.size(); }
std::vector<std::string>	Parser::getInputFile() const { return _inputFile; }
std::vector<std::string>::iterator Parser::getLine() const { return _line; }

/*--- INSERTION OVERLOAD -----------------------------------------------------*/

/* Print all servers info */
std::ostream& operator<<(std::ostream& os, const Parser& parser)
{
	for (size_t i = 0; i < parser.getServerSize(); ++i) {
		os << YELLOW "SERVER N." << i << RESET_COLOR << std::endl;
		os << parser.getServer(i);
	}
	return os;
}
