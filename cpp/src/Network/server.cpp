#include <sys/time.h>
#include <sys/socket.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "Network/server.hpp"
#include "Network/protocol.hpp"

uint8_t next_number;
struct sockaddr_in server_address;
char receipt_buf [MAX_RECV_LEN];
int receipt_len;
int socket_descriptor;
int port;
struct sockaddr_in client;

void initialize_server (int portno, int timeout, char* client_string_addr)
{
	struct timeval timeout_val;
	struct protocol_header sync_header;

	socket_descriptor = socket (AF_INET, SOCK_DGRAM, 0);

	memset ((char*)&server_address, 0, sizeof (struct sockaddr_in));
        server_address.sin_family = AF_INET;
        server_address.sin_addr.s_addr = htonl (INADDR_ANY);         
        server_address.sin_port = htons (portno);

	port = portno;

	timeout_val.tv_sec = 0;
	timeout_val.tv_usec = timeout;
	setsockopt (socket_descriptor, SOL_SOCKET, SO_RCVTIMEO, 
		    &timeout_val, sizeof (struct timeval));

	bind (socket_descriptor, (struct sockaddr*)&server_address,
	      sizeof (server_address));

	inet_pton (AF_INET, client_string_addr, &client.sin_addr);
	client.sin_family = AF_INET;
	client.sin_port = htons (port);

	next_number = 0;
	strcpy (sync_header.magic, SYNC_MAGIC);
	sync_header.len = 0;
	sync_header.number = 0;
	sendto (socket_descriptor, &sync_header, sizeof (struct protocol_header),
		0, (struct sockaddr*)&client, sizeof (client));
}

void send_command (char* command, int len)
{
	struct protocol_header command_header;
	struct protocol_header* receipt_header = (struct protocol_header*)&receipt_buf;
	socklen_t addrlen = sizeof (struct sockaddr_in);
	char command_buf [MAX_RECV_LEN];
	int recv_len;

	if (len > 2048 || len < 0)
	{
		printf ("Invalid command length\n");
		exit (-1);
	}

	strcpy (command_header.magic, COMMAND_MAGIC);
	command_header.len = len;
	command_header.number = next_number;
	memcpy (command_buf, &command_header, sizeof (struct protocol_header));
	memcpy (command_buf + sizeof (struct protocol_header), command, len);

	while (1)
	{
		sendto (socket_descriptor, command_buf,
			sizeof (struct protocol_header) + len, 0,
			(struct sockaddr*)&client, sizeof (client));

		recv_len = recvfrom (socket_descriptor, &receipt_buf,
				     MAX_RECV_LEN, 0, (struct sockaddr*)&client,
				     &addrlen);

		if (recv_len < (signed)sizeof (struct protocol_header))
			continue;
		else if (receipt_header->len >
		    MAX_RECV_LEN - sizeof (struct protocol_header))
			continue;
		else if (!strncmp (receipt_header->magic, SYNC_MAGIC, 4))
		{
			next_number = 0;
			command_header.number = next_number;
			memcpy (command_buf, &command_header, sizeof (struct protocol_header));
			memcpy (command_buf + sizeof (struct protocol_header), command, len);
			continue;
		}
		else if (strncmp (receipt_header->magic, RECEIPT_MAGIC, 4))
			continue;
		else if (receipt_header->number != next_number)
			continue;
		else
			break;
	}

	receipt_len = receipt_header->len;

	next_number ++;
}

char* get_receipt (void)
{
	return receipt_buf + sizeof (struct protocol_header);
}

void cleanup_server (void)
{
	close (socket_descriptor);
}
