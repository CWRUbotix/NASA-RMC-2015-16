#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <Robos/MessageBase.hpp>

namespace Network
{
	const size_t MAX_RECV_LEN = 2048 + sizeof (struct protocol_header;
	const char* COMMAND_MAGIC = "CMD";
 	const char* RECEIPT_MAGIC = "REC";
	const char* SYNC_MAGIC = "SYN";

	struct protocol_header
	{
		char magic [4]; //What type of signal are we receiving?
		uint16_t len; //Number of bytes in addition to protocol header.
		uint8_t number; //Used to keep track of order
	} protocol_header;

	struct client_init_data : public Robos::MessageBase
	{
		struct sockaddr_in return_address;
		struct sockaddr_in client_address;
		int socket_descriptor;

        client_init_data() : Robos::MessageBase("")
        {
        }

        ~client_init_data()
        {
        }

	} client_init_data;
}

#endif
