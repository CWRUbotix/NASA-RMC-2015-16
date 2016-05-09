#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "server.hpp"

int main (int argc, char** argv)
{
	if (argc != 2)
	{
		printf ("Error: please enter a command\n");
		exit (-1);
	}
	initialize_server (5005, 100, "192.168.0.2"); //IP address for the robot, subject to change
	send_commend (argv, strlen(argv) +1); //testing only, will eventually being setting up a continuous loop
	cleanup_server ();
}
