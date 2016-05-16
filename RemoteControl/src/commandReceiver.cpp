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
#include "../../cpp/include/CommonUtil/MotorUtil.hpp"

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
const char KEY_FORWARD = "KEY_UP";
const char KEY_BACKWARD = "KEY_DOWN";
const char KEY_CW = "KEY_LEFT";
const char KEY_CCW = "KEY_RIGHT";
const char KEY_DRIVEMOTORSTOP = "KEY_SPACE";
const char KEY_TURNCONFIGOPEN = "KEY_NUM5";
const char KEY_TURNCONFIGCLOSE = "KEY_NUM6";
const char KEY_TILTARMDOWN = "KEY_S";
const char KEY_TILTARMUP = "KEY_W";
const char KEY_TRANSLATEARMDOWN = "KEY_D";
const char KEY_TRANSLATEARMUP = "KEY_A";
const char KEY_BUCKETFORWARD = "KEY_F";
const char KEY_BUCKETREVERSE = "KEY_R";
const char KEY_HOPPEROUT= "KEY_H";
const char KEY_OVR = "KEY_O";

//key increments //to be experimentally determined
const double MOVEMENT_INC = 5.0;
const double TURN_INC = 2.0;
const double TILTARM_INC = 2.0;
const double TRANSLATEARM_INC = 3.0;
const double BUCKET_INC = 6.0;
const double HOPPER_INC = 1.0;

//store last two keystrokes
int lastKey = 0x00;
int currentKey = 0x00;

//speed keepers
double movementSpeed = 0.0;
double turnSpeed = 0.0;
double tiltArmSpeed = 0.0;
double translateArmSpeed = 0.0;
double bucketSpeed = 0.0;
double hopperSpeed = 0.0;

//command flags
enum translation = { off, up, down };
bool ovr = false;

Action action = NULL;
Action interpret_command (char* command) 
{
	lastKey = currentKey;
	currentKey = command;
	switch (currentKey)
	{
		case KEY_FORWARD:

			movementSpeed += MOVEMENT_INC;
			action = (movementSpeed > 0) ? forward(movementSpeed, ovr) : backward(movementSpeed, ovr);
			break;
		case KEY_BACKWARD:
			turnSpeed = 0.0;
			movementSpeed -= MOVEMENT_INC;
			action =  (movementSpeed > 0) ? forward(movementSpeed, ovr) : backward(movementSpeed, ovr);
			break;
		case KEY_CW:	
			movementSpeed = 0.0;
			tiltArmSpeed = 0.0;
			translateArmSpeed = 0.0;
			bucketSpeed = 0.0;
			hopperSpeed = 0.0;
			turnSpeed += TURN_INC;
			action = (turnSpeed > 0) ? turnLeft(turnSpeed, ovr) : turnRight(turnSpeed, ovr);
			break;
		case KEY_CCW:
			movementSpeed = 0.0;
			tiltArmSpeed = 0.0;
			translateArmSpeed = 0.0;
			bucketSpeed = 0.0;
			hopperSpeed = 0.0;
			turnSpeed -= TURN_INC;
			action = (turnSpeed > 0) ? turnLeft(turnSpeed, ovr) : turnRight(turnSpeed, ovr);
			break;
		case KEY_DRIVEMOTORSTOP:
			if (movementSpeed != 0.0) {
				movementSpeed = 0.0;
				action = forward(0.0, true);
			}
			else if (turnSpeed != 0.0) {
				turnSpeed = 0.0;
				action = turnLeft(0.0, true);
			}
			break;
		case KEY_TURNCONFIGOPEN:
			movementSpeed = 0.0;
			turnSpeed = 0.0;
			tiltArmSpeed = 0.0;
			translateArmSpeed = 0.0;
			bucketSpeed = 0.0;
			hopperSpeed = 0.0;
			action = openWheels(ovr);
			break;
		case KEY_TURNCONFIGCLOSE:
			movementSpeed = 0.0;
			turnSpeed = 0.0;
			tiltArmSpeed = 0.0;
			translateArmSpeed = 0.0;
			bucketSpeed = 0.0;
			hopperSpeed = 0.0;
			action = closeWheels(ovr);
			break;
		case KEY_TILTARMDOWN:
			movementSpeed = 0.0;
			turnSpeed = 0.0;
			bucketSpeed = 0.0;
			hopperSpeed = 0.0;
			tiltArmSpeed += TILTARM_INC;
			action (tiltArmSpeed > 0) ? tiltArmDown(tiltArmSpeed) : tiltArmUp(tiltArmSpeed);
			break;
		case KEY_TILTARMUP:
			movementSpeed = 0.0;
			turnSpeed = 0.0;
			bucketSpeed = 0.0;
			hopperSpeed = 0.0;
			tiltArmSpeed -= TILTARM_INC;
			action (tiltArmSpeed > 0) ? tiltArmDown(tiltArmSpeed) : tiltArmUp(tiltArmSpeed);
			break;
		case KEY_TRANSLATEARMDOWN:
			turnSpeed = 0.0;
			hopperSpeed = 0.0;
			tiltArmSpeed += TRANSLATEARM_INC;
			action (translateArmSpeed > 0) ? translateArmDown(translateArmSpeed) : translateArmUp(translateArmSpeed);
			break;
		case KEY_TRANSLATEARMUP:
			turnSpeed = 0.0;
			hopperSpeed = 0.0;
			tiltArmSpeed -= TILTARM_INC;
			action (translateArmSpeed > 0) ? translateArmDown(translateArmSpeed) : translateArmUp(translateArmSpeed);
			break;
		case KEY_BUCKETFORWARD:
			turnSpeed = 0.0;
			bucketSpeed += BUCKET_INC;
			action (bucketSpeed > 0) ? bucketForward(bucketSpeed) : bucketReverse(bucketSpeed);
			break;
		case KEY_BUCKETREVERSE:
			turnSpeed = 0.0;
			bucketSpeed -= BUCKET_INC;
			action (bucketSpeed > 0) ? bucketForward(bucketSpeed) : bucketReverse(bucketSpeed);
			break;
		case KEY_HOPPEROUT:
			turnSpeed = 0.0;
			hopperSpeed += HOPPER_INC;
			action (hopperSpeed > 0) ? hopperOut(hopperSpeed) : hopperIn(hopperSpeed);
			break;

		case KEY_OVR:
			ovr = !ovr;
			break;

		default:
			printf("That was not a valid key, bad driver.\n");
			break;
	}
	return action;
}
