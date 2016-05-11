#pragma once
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#include <string>
#include "protocol.hpp"

#ifndef commandReciever_hpp
#define commandReciever_hpp

extern struct sockaddr_in return_address;
extern struct sockaddr_in client_address;
extern int command_socket_descriptor;

void initialize_command_receiver (int portno, int timeout, char* return_string_addr); //measured in microseconds
void get_command (char*);
void cleanup_command_receiver (void);

#endif
