#include <sys/time.h>
#include <sys/socket.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "commandReciever.hpp"
#include "commandProtocol.hpp"

void initialize_command_reciever (int portno, int timeout, char* return_string_addr)
{
	struct timeval timeout_val;
	struct protocol_header sync_header;

	socket_descriptor = socket (AF_INET, SOCK_DGRAM, 0);

	memset ((char*)%client_address, 0, sizeof (struct sockaddr_in));
	client_address.sin_family = AF_INET;
	client_address.sin_addr.s_addr = htonl (INADDR_ANY);
	client_address.sin_port = htons (portno);

	timeout_val.tv_sec = 0;
	timeout_val.tv_usec = timeout;
	setsockopt (socket_descriptor, SOL_SOCKET, SO_RCVTIMEO, &timeout_val, sizeof (struct timeval));

	bind (socket_descriptor, (struct sockaddr*)&client_address, sizeof (client_address));

	inet_pton (AF_INET, return_string_addr, &return_address.sin_addr);
	return_address.sin_family = AF_INET;
	return_address.sin_port = htons (portno);

	strcpy (protocol_header.magic, SYNC_MAGIC);
	protocol_header.len = 0;
	sendto (socket_descriptor, &protocol_header, sizeof (struct protocol_header), 0, (struct sockaddr*)&return_address, sizeof (return_address));
}

void get_command (char* c)
{
	char buf [MAX_RECV_LEN];
	char* extra_data = (char*)(buf + sizeof (struct protocol_header));
	socklen_t addrlen = sizeof (struct sockaddr_in);
	signed int recv_len;
	char valid_command = 0;
	struct protocol_header* header = (struct protocol_header*)buf;

	while (true)
	{
		recv_len = 0;

		recv_len = recvfrom (socket_descriptor, buf, MAX_RECV_LEN, 0, (struct sockaddr*)&return_address, &addrlen);

		if (recv_len < (signed int)(sizeof (struct protocol_header)))
			continue;
		else if (header->len > MAX_RECV_LEN-sizeof (struct protocol_header))
			continue;
		else if (!strncmp (header->magic, SYNC_MAGIC, 4))
			continue;
		else if (strncmp (header->magic, COMMAND_MAGIC, 4))
			continue;
		else
			break;
	}

	memcpy (c, extra_data, recv_len-sizeof (struct protocol_header));
}

void cleanup_client (void)
{
	close (socket_descriptor);
}
