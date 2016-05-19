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

struct sockaddr_in client_address;
int command_socket_descriptor;
int clientfd;

void initialize_command_receiver (int portno)
{

	command_socket_descriptor = socket (AF_INET, SOCK_DGRAM, 0);

	memset ((char*)&client_address, 0, sizeof (struct sockaddr_in));
	client_address.sin_family = AF_INET;
	client_address.sin_addr.s_addr = INADDR_ANY;
	client_address.sin_port = htons (portno);

	bind (command_socket_descriptor, (struct sockaddr*)&client_address, sizeof (client_address));

	listen(command_socket_descriptor, 0);	
}

void get_command (char* c)
{
	char buf [MAX_RECV_LEN];

	while(true)
	{
		struct sockaddr_in client_addr;
		int addrlen=sizeof(client_addr);

		//accept a connection
		clientfd = accept(command_socket_descriptor, (struct sockaddr*)&client_addr, (socklen_t*)&addrlen);

		//store anything recieved
		recv(clientfd, buf, MAX_RECV_LEN, 0);
		c = buf;
	}
}

void cleanup_command_receiver (void)
{
	close (clientfd);
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
			next_action = MotorControl::stopAll();
			action = &next_action;

		default:
			printf("That was not a valid key, bad driver.\n");
			break;
	}
	return action;
}

}
