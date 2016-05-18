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
#include <iostream>

int main() {
	initialize_client(5005, 100, "127.0.0.1");
	//MotorControl::initialize("/dev/ttyACM2");
	printf("Start listening");
	char command[MAX_RECV_LEN];
	while(1) {
		get_command(command);
		MotorControl::Action a(command+3,MAX_RECV_LEN-3);
		char out[1];
		out[0] = '0' + a.num_motors;
		send_reply(out, 1);
		std::cout << a.num_motors << "\n";
	}
	return 0;
}



