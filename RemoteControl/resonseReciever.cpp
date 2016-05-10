#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "client.h"

int main (int argc, char** argv)
{
	if (argc != 2)
	{
		prinf("Error: please enter the robot IP");
		exit(-1);
	}
	initialize_client (5006, 100, argv[1]);
	char* command = "";
	while(command != 'q')
	{
		command = get_command();
		printf("%s\n", command);
	}
	cleanup_client();
}
