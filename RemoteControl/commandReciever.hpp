#include <arpa/inet.h>
#include <sys/socket.h>
#include "protocol.hpp"

#ifndef commandReciever_hpp
#define commandReciever_hpp

struct sockaddr_in return_address;
struct sockaddr_in client_address;
int socket_descriptor;

void initialize_command_reciever (int portno, int timeout, std::string return_string_addr); //measured in microseconds
void get_command (char*);
void cleanup_command_reciever (void);

#endif
