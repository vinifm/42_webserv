#include "Listen.hpp"

Listen::Listen() {}
Listen::~Listen() {}

void Listen::_setPort(const std::string& word)
{
	std::stringstream	port_str(word);
	if (port_str >> _port)
		throw std::runtime_error("invalid listen port");
}

void	Listen::initListen(std::stringstream& values)
{
	std::string			word;
	size_t				colon_pos;
	size_t				dot_pos;

	while (values >> word) {
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
}

std::ostream& operator<<(std::ostream& os, const Listen& listen)
{
	std::cout << "Address: " << listen.getAddress()
		<< "Port: " << listen.getPort()
		<<std::endl;
}

/*--- GETTERS ----------------------------------------------------------------*/

std::string	Listen::getAddress() const { return _address; }
int			Listen::getPort() const { return _port; }
