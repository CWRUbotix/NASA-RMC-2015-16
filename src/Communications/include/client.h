#include <sys/socket.h>
#include "protocol.h"

#ifndef client_h
#define client_h

uint8_t next_number;
struct sockaddr_in return_address;
struct sockaddr_in client_address;
int socket_descriptor;

void initialize_client (int portno, int timeout, char* return_string_addr); //measured in microseconds
char* get_command (void);
void send_reply (char* reply, int len);
void cleanup_client (void);

#endif
