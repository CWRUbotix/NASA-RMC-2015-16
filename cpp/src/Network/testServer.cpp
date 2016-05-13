#include "Network/server.hpp"
#include <memory>
#include <iostream>
#include <string.h>
#include <string>

int main()
{
	initialize_server(5001, 100, "127.0.0.1");
	char* command = "THIS FREAKING WORKS HA!";
	send_command(command, strlen(command) + 1);
	printf("%s\n", get_receipt());
	cleanup_server();
	exit(1);
}
