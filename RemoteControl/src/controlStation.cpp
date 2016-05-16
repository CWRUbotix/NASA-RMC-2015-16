#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "server.hpp"
#include "commandReceiver.hpp"

int main (int argc, char** argv)
{
	if (argc != 2)
	{
		printf ("Error: please enter an IP address.\n");
		exit (-1);
	}
		
	//get computer's IP
	char* my_ip;
	FILE* out = popen("ifconfig wlan0 | grep \"inet addr:\" | cut -d: -f2 | cut -d''-f1", "r");
	fgets(my_ip, sizeof(my_ip)-1, out);

	initialize_server (5005, 100, argv[0]); //open socket at port 5005 at given IP with timeout of 100
	initialize_command_receiver (5007, 100, my_ip);

	char* command; //change the length of the input command to max length of a command
	while (command[0] != 'q')
	{
		get_command(command);

		switch (command)
		{
			
		}

		send_command (command, strlen(command) +1); //send the command
		printf ("%s", get_receipt()); //get response
	}
	cleanup_server();
	cleanup_command_receiver();
	exit(1);
}
