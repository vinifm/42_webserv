#include <Utils.hpp>

int main(void)
{
	print_banner();
	Socket	server(8080, "www/default2/");

	server.init();
	while (true)
	{
		if (server.get_next_connection())
			server.send_response();
	}
	server.deinit();
	print_log("main.cpp", "webserv is off 🔴");
	return (0);
}
