#include <Utils.hpp>

int main(void)
{
	// LOAD SOME CONFIG FILES JUST FOR TEST
	Socket	server(8080, "www/default/");

	server.init();
	while (true)
	{
		if (server.wait_request())
		{
			if (server.request_is_valid())
				server.send_response("");
		}
	}
	server.deinit();
	return (0);
}
