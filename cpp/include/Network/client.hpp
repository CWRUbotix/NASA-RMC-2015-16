#pragma once
#ifndef client_h
#define client_h

#include <arpa/inet.h>
#include <sys/socket.h>
#include "Network/protocol.hpp"
#include <string>

extern uint8_t next_number;
extern struct sockaddr_in return_address;
extern struct sockaddr_in client_address;
extern int socket_descriptor;

void initialize_client (int portno, int timeout, char* return_string_addr); //measured in microseconds
void get_command (char*);
void send_reply (char* reply, int len);
void cleanup_client (void);

#endif
