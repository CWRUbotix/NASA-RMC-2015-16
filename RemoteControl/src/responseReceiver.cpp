#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "client.hpp"

int main (int argc, char** argv)
{
	if (argc != 2)
	{
		printf("Error: please enter the robot IP\n");
		exit(-1);
	}
	initialize_client (5006, 100, argv[1]);
	char* command;
	while(command[0] != 'q')
	{
		get_command(command);
		printf("%s\n", command);
	}
	cleanup_client();
	exit(1);
}
