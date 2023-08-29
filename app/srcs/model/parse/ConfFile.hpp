#ifndef CONFFILE_HPP
#define CONFFILE_HPP

class ConfFile
{
private:
	std::string	_root;
	int			_port;

public:
	//occf
	ConfFile(void);
	ConfFile(std::string path);
	~ConfFile(void);

	//methods
	int 	is_valid(void);

	//getters && setters
	int				getPort(void);
	int				setPort(void);
	std::string		getRoot(void);
	std::string		setRoot(void);

};

#endif