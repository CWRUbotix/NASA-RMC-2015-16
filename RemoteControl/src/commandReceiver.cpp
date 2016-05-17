#include <sys/time.h>
#include <sys/socket.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include "commandReceiver.hpp"
#include "commandProtocol.hpp"

namespace Network {

struct sockaddr_in return_address;
struct sockaddr_in client_address;
int command_socket_descriptor;

void initialize_command_receiver (int portno, int timeout, char* return_string_addr)
{
	struct timeval timeout_val;
	struct protocol_header sync_header;

	command_socket_descriptor = socket (AF_INET, SOCK_DGRAM, 0);

	memset ((char*)&client_address, 0, sizeof (struct sockaddr_in));
	client_address.sin_family = AF_INET;
	client_address.sin_addr.s_addr = htonl (INADDR_ANY);
	client_address.sin_port = htons (portno);

	timeout_val.tv_sec = 0;
	timeout_val.tv_usec = timeout;
	setsockopt (command_socket_descriptor, SOL_SOCKET, SO_RCVTIMEO, &timeout_val, sizeof (struct timeval));

	bind (command_socket_descriptor, (struct sockaddr*)&client_address, sizeof (client_address));

	inet_pton (AF_INET, return_string_addr, &return_address.sin_addr);
	return_address.sin_family = AF_INET;
	return_address.sin_port = htons (portno);

	strcpy (sync_header.magic, SYNC_MAGIC);
	sync_header.len = 0;
	sendto (command_socket_descriptor, &sync_header, sizeof (struct protocol_header), 0, (struct sockaddr*)&return_address, sizeof (return_address));
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

		recv_len = recvfrom (command_socket_descriptor, buf, MAX_RECV_LEN, 0, (struct sockaddr*)&return_address, &addrlen);

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

void cleanup_command_receiver (void)
{
	close (command_socket_descriptor);
}

//keys //will be hexvalues for each key
const char KEY_FORWARD = 0x4C; //up arrow
const char KEY_BACKWARD = 0x4D; //down arrow
const char KEY_CW = 0x4E; //right arrow
const char KEY_CCW = 0x4F; //left arrow
const char KEY_DRIVEMOTORSTOP = 0x40; //spacebar
const char KEY_TURNCONFIGOPEN = 0x39; //.
const char KEY_TURNCONFIGCLOSE = 0x3A; ///
const char KEY_TILTARMDOWN = 0x21; //s
const char KEY_TILTARMUP = 0x11; //w
const char KEY_TRANSLATEARMDOWN = 0x22; //d
const char KEY_TRANSLATEARMUP = 0x20; //a
const char KEY_BUCKETFORWARD = 0x23; //f
const char KEY_BUCKETBACKWARD = 0x13; //r
const char KEY_HOPPEROUT= 0x25; //h
const char KEY_OVR = 0x18; //o
const char KEY_STOPALL = 0x45; //esc

//key increments //to be experimentally determined
const double MOVEMENT_INC = 5.0;
const double TURN_INC = 2.0;
const double TRANSLATEARM_INC = 3.0;
const double BUCKET_INC = 6.0;
const double HOPPER_INC = 1.0;
const double TILTARM_SPEED = 2.0;

//store last two keystrokes
int lastKey = 0x00;
int currentKey = 0x00;

//speed keepers
double movementSpeed = 0.0;
double turnSpeed = 0.0;
double translateArmSpeed = 0.0;
double bucketSpeed = 0.0;
double hopperSpeed = 0.0;

//command flags
enum TiltAngle tiltAngle = minAngle;
bool ovr = false;

MotorControl::Action* interpret_command (char command) 
{
	MotorControl::Action* action = nullptr;
	MotorControl::Action next_action;
	
	switch (command)
	{
		case KEY_FORWARD:
			turnSpeed = 0.0;
			movementSpeed += MOVEMENT_INC;
			next_action = (movementSpeed > 0) ? MotorControl::forward(movementSpeed, ovr) : MotorControl::backward(movementSpeed, ovr);
			action = &next_action;
			break;
		case KEY_BACKWARD:
			turnSpeed = 0.0;
			movementSpeed -= MOVEMENT_INC;
			next_action = (movementSpeed > 0) ? MotorControl::forward(movementSpeed, ovr) : MotorControl::backward(movementSpeed, ovr);
			action = &next_action;
			break;
		case KEY_CW:	
			movementSpeed = 0.0;
			translateArmSpeed = 0.0;
			bucketSpeed = 0.0;
			hopperSpeed = 0.0;
			turnSpeed += TURN_INC;
			next_action = (turnSpeed > 0) ? MotorControl::turnLeft(turnSpeed, ovr) : MotorControl::turnRight(turnSpeed, ovr);
			action = &next_action;
			break;
		case KEY_CCW:
			movementSpeed = 0.0;
			translateArmSpeed = 0.0;
			bucketSpeed = 0.0;
			hopperSpeed = 0.0;
			turnSpeed -= TURN_INC;
			next_action = (turnSpeed > 0) ? MotorControl::turnLeft(turnSpeed, ovr) : MotorControl::turnRight(turnSpeed, ovr);
			action = &next_action;
			break;
		case KEY_DRIVEMOTORSTOP:
			if (movementSpeed != 0.0) {
				movementSpeed = 0.0;
				next_action = MotorControl::forward(0.0, true);
				action = &next_action;
			}
			else if (turnSpeed != 0.0) {
				turnSpeed = 0.0;
				next_action = MotorControl::turnLeft(0.0, true);
				action = &next_action;
			}
			break;
		case KEY_TURNCONFIGOPEN:
			movementSpeed = 0.0;
			turnSpeed = 0.0;
			translateArmSpeed = 0.0;
			bucketSpeed = 0.0;
			hopperSpeed = 0.0;
			next_action = MotorControl::openWheels(ovr);
			action = &next_action;
			break;
		case KEY_TURNCONFIGCLOSE:
			movementSpeed = 0.0;
			turnSpeed = 0.0;
			translateArmSpeed = 0.0;
			bucketSpeed = 0.0;
			hopperSpeed = 0.0;
			next_action = MotorControl::closeWheels(ovr);
			action = &next_action;
			break;
		case KEY_TILTARMDOWN:
			movementSpeed = 0.0;
			turnSpeed = 0.0;
			bucketSpeed = 0.0;
			hopperSpeed = 0.0;
			if (tiltAngle == minAngle) {
				next_action = MotorControl::tiltArmDown(TILTARM_SPEED, midAngle);
				action = &next_action;
			}
			else if (tiltAngle == midAngle) {
				next_action = MotorControl::tiltArmDown(TILTARM_SPEED, maxAngle);
				action = &next_action;
			}
			else if (tiltAngle == maxAngle) {
				printf("Arm is already at maximum down.\n");
			}
			break;
		case KEY_TILTARMUP:
			movementSpeed = 0.0;
			turnSpeed = 0.0;
			bucketSpeed = 0.0;
			hopperSpeed = 0.0;
			if (tiltAngle == minAngle) {
				printf("Arm is already at maximum up.\n");
			}
			else if (tiltAngle == midAngle) {
				next_action = MotorControl::tiltArmUp(TILTARM_SPEED, minAngle);
				action = &next_action;
			}
			else if (tiltAngle == maxAngle) {
				next_action = MotorControl::tiltArmUp(TILTARM_SPEED, midAngle);
				action = &next_action;
			}
			break;
		case KEY_TRANSLATEARMDOWN:
			turnSpeed = 0.0;
			hopperSpeed = 0.0;
			translateArmSpeed += TRANSLATEARM_INC;
			next_action = (translateArmSpeed > 0) ? MotorControl::translateArmDown(translateArmSpeed) : MotorControl::translateArmUp(translateArmSpeed);
			action = &next_action;
			break;
		case KEY_TRANSLATEARMUP:
			turnSpeed = 0.0;
			hopperSpeed = 0.0;
			translateArmSpeed -= TRANSLATEARM_INC;
			next_action = (translateArmSpeed > 0) ? MotorControl::translateArmDown(translateArmSpeed) : MotorControl::translateArmUp(translateArmSpeed);
			action = &next_action;
			break;
		case KEY_BUCKETFORWARD:
			turnSpeed = 0.0;
			bucketSpeed += BUCKET_INC;
			next_action = (bucketSpeed > 0) ? MotorControl::bucketForward(bucketSpeed) : MotorControl::bucketBackward(bucketSpeed);
			action = &next_action;
			break;
		case KEY_BUCKETBACKWARD:
			turnSpeed = 0.0;
			bucketSpeed -= BUCKET_INC;
			next_action = (bucketSpeed > 0) ? MotorControl::bucketForward(bucketSpeed) : MotorControl::bucketBackward(bucketSpeed);
			action = &next_action;
			break;
		case KEY_HOPPEROUT:
			turnSpeed = 0.0;
			hopperSpeed += HOPPER_INC;
			if (hopperSpeed > 0) {
				next_action = MotorControl::hopperOut(hopperSpeed);
				action = &next_action;
			}
			break;

		case KEY_OVR:
			ovr = !ovr;
			break;

		case KEY_STOPALL:
			movementSpeed = 0.0;
			turnSpeed = 0.0;
			translateArmSpeed = 0.0;
			bucketSpeed = 0.0;
			hopperSpeed = 0.0;
			action = MotorControl::stopAll();
			action = &next_action;

		default:
			printf("That was not a valid key, bad driver.\n");
			break;
	}
	return action;
}

}
