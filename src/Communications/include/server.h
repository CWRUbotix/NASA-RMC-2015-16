#include <sys/socket.h>
#include "protocol.h"

#ifndef server_h
#define server_h

uint8_t next_number;
struct sockaddr_in server_address;
char receipt_buf [MAX_RECV_LEN];
int receipt_len;
int socket_descriptor;
int port;
struct sockaddr_in client;

void initialize_server (int portno, int timeout, char* client_string_addr); //Timeout measured in microseconds
void send_command (char* command, int len);
char* get_receipt (void);
void cleanup_server (void);

#endif
