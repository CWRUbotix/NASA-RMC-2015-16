#include <arpa/inet.h>
#include <sys/socket.h>
#include "protocol.hpp"

#ifndef client_h
#define client_h

uint8_t next_number;
struct sockaddr_in return_address;
struct sockaddr_in client_address;
int socket_descriptor;

void initialize_client (int portno, int timeout, std::string return_string_addr); //measured in microseconds
void get_command (char*);
void send_reply (char* reply, int len);
void cleanup_client (void);

#endif
