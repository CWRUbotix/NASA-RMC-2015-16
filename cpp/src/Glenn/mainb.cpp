/*
 * mainb.cpp
 *
 *  Created on: May 17, 2016
 *      Author: root
 */
#include "Network/client.hpp"
#include "MotorControl/MotorControl.hpp"
#include "CommonUtil/MotorUtil.hpp"
#include "USBSerial/USBSerial.hpp"
#include "Network/protocol.hpp"

int main(int argc, char** argv) {
	if (argc != 2) {
		printf("Please input an IP address.\n");
		exit(-1);
	}

	initialize_client(5005, 100, argv[0]);
	//MotorControl::initialize("/dev/ttyACM2");
	printf("Start listening.\n");
	char command[MAX_RECV_LEN];
	while(1) {
		get_command(command);
		printf("Got command\n");
		send_reply ((char *)"msg rcvd\n", strlen ("msg rcvd\n") + 1);
		MotorControl::Action a;
		switch (command[0])
		{
		case 1:
			a = MotorControl::Action(command+3,MAX_RECV_LEN-3);
			MotorControl::queueAction(a);
			break;
		default:
			printf("ERROR: message recieved not formattted correctly");
			break;
		}
	}
	return 0;
}



