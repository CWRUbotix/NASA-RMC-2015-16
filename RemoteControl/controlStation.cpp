#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "server.hpp"
#include "commandReciever.hpp"

int main (int argc, char** argv)
{
	if (argc != 2)
	{
		printf ("Error: please enter an IP address.\n");
		exit (-1);
	}

	initialize_server (5005, 100, argv[0]); //open socket at port 5005 at given IP with timeout of 100
	initialize_command_reciever (5007, 100, ); //need to add own IP address

	char* command; //change the length of the input command to max length of a command
	while (command[0] != 'q')
	{
		command = get_command();
		send_command (command, strlen(command) +1); //send the command
		printf ("%s", get_receipt()); //get response
	}
	cleanup_server();
	exit(1);
}
