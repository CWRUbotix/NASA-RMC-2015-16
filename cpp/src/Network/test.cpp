#include "Network/client.hpp"
#include "Network/server.hpp"
#include <memory>
#include <iostream>

int main() {
	initialize_client(5001, 100, "127.0.0.1");
	initialize_server(5001, 100, "127.0.0.1");
	send_command("Hello",5);
	char* in = (char*) ::malloc(5);
	get_command(in);
	std::cout << in << "\n";
	return 0;
}

