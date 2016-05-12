#include "Network/client.hpp"
#include "Network/server.hpp"
#include <memory>
#include <iostream>

int main() {
	initialize_client(5001, 100, "127.0.0.1");
	char* command;
	get_command(command);
	printf("%s\n", command);
	char* reply = "I TOLD YOU THAT THIS WORKS!";
	send_reply(reply, strlen(reply) + 1);
	cleanup_client();
	exit(1);
}

