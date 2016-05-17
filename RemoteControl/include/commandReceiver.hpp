#pragma once
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#include <string>
#include "protocol.hpp"
#include "../../cpp/include/CommonUtil/MotorUtil.hpp"

#ifndef commandReciever_hpp
#define commandReciever_hpp

namespace Network {

extern struct sockaddr_in return_address;
extern struct sockaddr_in client_address;
extern int command_socket_descriptor;

void initialize_command_receiver (int portno, int timeout, char* return_string_addr); //measured in microseconds
void get_command (char*);
void cleanup_command_receiver (void);

MotorControl::Action* interpret_command (char);

enum TiltAngle { minAngle = 0, midAngle = 60, maxAngle = 90 };

}

#endif
