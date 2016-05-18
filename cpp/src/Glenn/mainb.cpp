/*
 * mainb.cpp
 *
 *  Created on: May 17, 2016
 *      Author: root
 */
#include <string.h>
#include "Network/client.hpp"
#include "MotorControl/MotorControlSimple.hpp"
#include "CommonUtil/MotorUtil.hpp"
#include "USBSerial/USBSerial.hpp"
#include "Network/protocol.hpp"
#include "Control/commandReceiver.hpp"

int main(int argc, char** argv) {
	/*
	if (argc != 2) {
		printf("Please input an IP address.\n");
		exit(-1);
	}
	 */

	//initialize_client(5005, 100, argv[0]);
	MotorControl::initialize("/dev/ttyACM2");
	sleep(1);
	printf("Start listening.\n");
	char command[MAX_RECV_LEN];
	while(1) {
		//get_command(command);
		//printf("Got command\n");
		//send_reply ((char *)"msg rcvd\n", strlen ("msg rcvd\n") + 1);

		printf("Please enter a hex command.\n");
		scanf("%s", command);

		std::string command_string = std::string(command);
		//char command_hex = std::stoul(command_string, NULL, 16);
		switch(command[0]) {
		case 'w':
			uint8_t m[4] = {MOT_FR,MOT_FL,MOT_BR,MOT_BL};
			bool d[4] = {true,true,true,true};
			MotorControl::ActionSimple action(m,d,4,125);
			MotorControl::queueAction(action);
			break;
		case 's':
			uint8_t m[4] = {MOT_FR,MOT_FL,MOT_BR,MOT_BL};
			bool d[4] = {false,false,false,false};
			MotorControl::ActionSimple action(m,d,4,125);
			MotorControl::queueAction(action);
			break;
		case 'a':
			uint8_t m[4] = {MOT_FR,MOT_FL,MOT_BR,MOT_BL};
			bool d[4] = {true,false,true,false};
			MotorControl::ActionSimple action(m,d,4,125);
			MotorControl::queueAction(action);
		}

		if(command[0] == 'w') {
			uint8_t m[4] = {MOT_FR,MOT_FL,MOT_BR,MOT_BL};
			bool d[4] = {true,true,true,true};
			MotorControl::ActionSimple action(m,d,4,125);
			MotorControl::queueAction(action);
		} else if(command){
			uint8_t m1[4] = {MOT_BR,MOT_BL,MOT_FR,MOT_FL};
			bool d1[4] = {true,true,true,true};
			MotorControl::ActionSimple action1(m1,d1,4,1);
			MotorControl::queueAction(action1);
		}
		/*
		MotorControl::Action* a_ptr = Network::interpret_command(command_hex);
		MotorControl::Action a;
		memcpy(&a, a_ptr, sizeof(MotorControl::Action));

		switch (command[0])
		{
		case 1:
			a = MotorControl::Action(command+3,MAX_RECV_LEN-3);
			MotorControl::queueAction(a);
			break;
		default:
			printf("ERROR: message recieved not formattted correctly");
			break;
		}*/
	}
	return 0;
}



