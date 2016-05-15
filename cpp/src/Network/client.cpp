#include <sys/time.h>
#include <sys/socket.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "Network/protocol.hpp"
#include "Network/client.hpp"

/*
#include <Logging/ILogger.hpp>
#include <Logging/Factory.hpp>
#include "NetworkingConfig.hpp"

Logging::LoggerPtr pLogger = NULL;

Logging::LoggerPtr GetStaticLogger()
{
    if(!pLogger)
        pLogger = Logging::Factory::MakeLogger("Networking_Client_Logger",
                                               (Networking::Config::LOGGING_ROOT + "/ClientLog.txt").c_str());
    return pLogger;
}
*/

uint8_t next_number;
struct sockaddr_in return_address;
struct sockaddr_in client_address;
int socket_descriptor;

void initialize_client (int portno, int timeout, char* return_string_addr)
{

	struct timeval timeout_val;
	// struct protocol_header sync_header;

	socket_descriptor = socket (AF_INET, SOCK_DGRAM, 0);

	memset ((char*)&client_address, 0, sizeof (struct sockaddr_in));
        client_address.sin_family = AF_INET;                         
        client_address.sin_addr.s_addr = htonl (INADDR_ANY);         
        client_address.sin_port = htons (portno);

	timeout_val.tv_sec = 0;
	timeout_val.tv_usec = timeout;
	setsockopt (socket_descriptor, SOL_SOCKET, SO_RCVTIMEO, 
		    &timeout_val, sizeof (struct timeval));

	bind (socket_descriptor, (struct sockaddr*)&client_address, 
	      sizeof (client_address));

	inet_pton (AF_INET, return_string_addr, &return_address.sin_addr);
	return_address.sin_family = AF_INET;
	return_address.sin_port = htons (portno);

	next_number = 0;
	strcpy (sync_header.magic, SYNC_MAGIC);
	sync_header.len = 0;
	sync_header.number = 0;
	sendto (socket_descriptor, &sync_header, sizeof (struct protocol_header),
		0, (struct sockaddr*)&return_address, sizeof (return_address));
		
}

void get_command (char* c)
{
  //   LOG_DEBUG(GetStaticLogger(), "I am Logging!");
	char buf [MAX_RECV_LEN];
	char* extra_data = (char*)(buf + sizeof (struct protocol_header));
	socklen_t addrlen = sizeof (struct sockaddr_in);
	signed int recv_len;
	// char valid_command = 0;
	struct protocol_header* header = (struct protocol_header*)buf;

	while (1)
	{
		recv_len = 0;

		recv_len = recvfrom (socket_descriptor, buf, MAX_RECV_LEN, 0, 
				     (struct sockaddr*)&return_address, &addrlen);

		if (recv_len < (signed int)(sizeof (struct protocol_header)))
			continue;
		else if (header->len > MAX_RECV_LEN-sizeof (struct protocol_header))
			continue;
		else if (!strncmp (header->magic, SYNC_MAGIC, 4))
		{
			next_number = 0;
			continue;
		}
		else if (strncmp (header->magic, COMMAND_MAGIC, 4))
			continue;
		else if (header->number != next_number)
			continue;
		else
			break;
	}

	next_number ++;

	memcpy (c, extra_data, recv_len-sizeof (struct protocol_header));
}

void send_reply (char* reply, int len)
{
	struct protocol_header receipt_header;
	char buf [MAX_RECV_LEN];

	if (len > 2048 || len < 0)
	{
		printf ("Error: invalid packet length\n");
		exit (-1);
	}

	strcpy (receipt_header.magic, RECEIPT_MAGIC);
	receipt_header.len = len;
	receipt_header.number = next_number - 1;

	memcpy (buf, &receipt_header, sizeof (struct protocol_header));
	memcpy (buf + sizeof (struct protocol_header), reply, len);

	sendto (socket_descriptor, buf, len + sizeof (struct protocol_header),
		0, (struct sockaddr*)&return_address, sizeof (return_address));
}

void cleanup_client (void)
{
	close (socket_descriptor);
}
