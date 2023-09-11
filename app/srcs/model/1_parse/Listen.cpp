#include "Listen.hpp"

Listen::Listen() : _address("*"), _port(80) {}
Listen::~Listen() {}

void Listen::_setPort(const std::string& word)
{
	std::stringstream	port_str(word);
	if (!(port_str >> _port))
		throw std::runtime_error("invalid listen port");
}

void	Listen::initListen(std::stringstream& values)
{
	std::string			word;
	size_t				colon_pos;
	size_t				dot_pos;
	int					valid = 0;

	while (values >> word) {
		valid = 1;
		colon_pos = word.find(":");
		dot_pos = word.find(".");
		if (colon_pos != std::string::npos) {
			_address = word.substr(0, colon_pos);
			_setPort(word.substr(colon_pos + 1));
		}
		else if (dot_pos != std::string::npos)
			_address = word;
		else
			_setPort(word.substr(colon_pos + 1));
	}
	if (!valid)
		throw std::runtime_error("listen: missing options");
}

std::ostream& operator<<(std::ostream& os, const Listen& listen)
{
	os << "Listen:\n\tAddress: " << listen.getAddress()
		<< "\n\tPort: " << listen.getPort();
	return os;
}

/*--- GETTERS ----------------------------------------------------------------*/

std::string	Listen::getAddress() const { return _address; }
int			Listen::getPort() const { return _port; }
