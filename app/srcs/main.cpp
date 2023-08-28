#include <Utils.hpp>

int main(void)
{
	print_banner();
	Socket	server(8080, "www/default/");

	server.init();
	while (true)
	{
		if (server.get_next_connection())
		{
			if (server.request_is_valid())
				server.send_response("");
		}
	}
	server.deinit();
	print_log("main.cpp", "webserv is off 🔴");
	return (0);
}
