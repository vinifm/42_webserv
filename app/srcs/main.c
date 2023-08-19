#include <Webserv.hpp>

int main(void)
{
	Socket	s;

	s.init(PORT);
	while (true)
	{
		if (s.wait_request())
		{
			std::string	response = s.load_page("www/default2/index.html");
			if (response.empty())
				return (0);
			s.send_response(response);
		}
	}
	s.deinit();
	return (0);
}
