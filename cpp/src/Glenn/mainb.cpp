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

		printf("Please enter a v command.\n");
		scanf("%s", command);


		if(command[0] == 'w') {
			uint8_t m[4] = {MOT_FR,MOT_FL,MOT_BR,MOT_BL};
			bool d[4] = {false,true,false,true};
			MotorControl::ActionSimple action(m,d,4,100);
			MotorControl::queueAction(action);
		} else if(command[0] == 's') {
			uint8_t m[4] = {MOT_FR,MOT_FL,MOT_BR,MOT_BL};
			bool d[4] = {true,false,true,false};
			MotorControl::ActionSimple action(m,d,4,100);
			MotorControl::queueAction(action);
		} else if(command[0] == 'd') {
			uint8_t m[4] = {MOT_FR,MOT_FL,MOT_BR,MOT_BL};
			bool d[4] = {true,true,true,true};
			MotorControl::ActionSimple action(m,d,4,100);
			MotorControl::queueAction(action);
		} else if(command[0] == 'a') {
			uint8_t m[4] = {MOT_FR,MOT_FL,MOT_BR,MOT_BL};
			bool d[4] = {false,false,false,false};
			MotorControl::ActionSimple action(m,d,4,100);
			MotorControl::queueAction(action);
		} else if(command[0] == 'e') {
			uint8_t m[2] = {MOT_TRAL,MOT_TRAR};
			bool d[4] = {true,true};
			MotorControl::ActionSimple action(m,d,2,40);
			MotorControl::queueAction(action);
		} else if(command[0] == 'r') {
			uint8_t m[2] = {MOT_TRAL,MOT_TRAR};
			bool d[4] = {false,false};
			MotorControl::ActionSimple action(m,d,2,40);
			MotorControl::queueAction(action);
		} else if(command[0] == 'q') {
			uint8_t m[2] = {MOT_TRAL,MOT_TRAR};
			bool d[4] = {false,false};
			MotorControl::ActionSimple action(m,d,2,0);
			MotorControl::queueAction(action);
		} else if(command[0] == 'x') {
			uint8_t m[1] = {MOT_CBUC};
			bool d[4] = {true};
			MotorControl::ActionSimple action(m,d,1,100);
			MotorControl::queueAction(action);
		} else if(command[0] == 'v') {
			uint8_t m[1] = {MOT_CHOP};
			bool d[4] = {false};
			MotorControl::ActionSimple action(m,d,1,40);
			MotorControl::queueAction(action);
		} else if(command[0] == 'z') {
			uint8_t m[1] = {MOT_CBUC};
			bool d[4] = {true};
			MotorControl::ActionSimple action(m,d,1,0);
			MotorControl::queueAction(action);
		} else if(command[0] == 'c') {
			uint8_t m[1] = {MOT_CHOP};
			bool d[4] = {false};
			MotorControl::ActionSimple action(m,d,1,0);
			MotorControl::queueAction(action);
		}
/*
		if(command[0] == 'p') {
			MotorControl::port.close();
			printf("Closing port\n");
			sleep(1);
			MotorControl::port.open();
			sleep(1);
			printf("Opening port\n");
		} else if(command[0] == 'z') {
			uint8_t m[5] = {MOT_FR,MOT_FL,MOT_BR,MOT_BL,MOT_CHOP};
			bool d[5] = {false,true,false,true,true};
			MotorControl::ActionSimple action(m,d,5,0);
			MotorControl::queueAction(action);
		}else if(command[0] == 'w') {
			uint8_t m[4] = {MOT_FR,MOT_FL,MOT_BR,MOT_BL};
			bool d[4] = {false,true,false,true};
			MotorControl::ActionSimple action(m,d,4,125);
			MotorControl::queueAction(action);
		} else if(command[0] == 's') {
			uint8_t m[4] = {MOT_FR,MOT_FL,MOT_BR,MOT_BL};
			bool d[4] = {true,false,true,false};
			MotorControl::ActionSimple action(m,d,4,125);
			MotorControl::queueAction(action);
		} else if(command[0] == 'a') {
			uint8_t m[4] = {MOT_FR,MOT_FL,MOT_BR,MOT_BL};
			bool d[4] = {false,false,false,false};
			MotorControl::ActionSimple action(m,d,4,125);
			MotorControl::queueAction(action);
		} else if(command[0] == 'd') {
			uint8_t m[4] = {MOT_FR,MOT_FL,MOT_BR,MOT_BL};
			bool d[4] = {true,true,true,true};
			MotorControl::ActionSimple action(m,d,4,125);
			MotorControl::queueAction(action);
		} else if(command[0] == 'q') {
			uint8_t m[2] = {ACT_WHEL,ACT_WHER};
			bool d[4] = {true,true};
			MotorControl::ActionSimple action(m,d,2,125);
			MotorControl::queueAction(action);
			std::this_thread::sleep_for(std::chrono::milliseconds(200));
			MotorControl::ActionSimple action1(m,d,2,0);
			MotorControl::queueAction(action1);
		} else if(command[0] == 'e') {
			uint8_t m[2] = {ACT_WHEL,ACT_WHER};
			bool d[4] = {false,false};
			MotorControl::ActionSimple action(m,d,2,125);
			MotorControl::queueAction(action);
			std::this_thread::sleep_for(std::chrono::milliseconds(200));
			MotorControl::ActionSimple action1(m,d,2,0);
			MotorControl::queueAction(action1);
		} else if(command[0] == 'h') {
			uint8_t m[1] = {MOT_CHOP};
			bool d[4] = {false};
			MotorControl::ActionSimple action(m,d,1,40);
			MotorControl::queueAction(action);
		} else if (command[0] == 'y') {
			uint8_t m[1] = {MOT_CHOP};
			bool d[4] = {false};
			MotorControl::ActionSimple action(m,d,1,0);
			MotorControl::queueAction(action);
		} else if(command[0] == 'b') {
			uint8_t m[1] = {MOT_CBUC};
			bool d[4] = {true};
			MotorControl::ActionSimple action(m,d,1,100);
			MotorControl::queueAction(action);
			std::this_thread::sleep_for(std::chrono::milliseconds(400));
			MotorControl::ActionSimple action1(m,d,1,0);
			MotorControl::queueAction(action1);
		} else if(command[0] == 't') {
			// Left true is up
			uint8_t m[2] = {MOT_TRAL,MOT_TRAR};
			bool d[4] = {true,true};
			MotorControl::ActionSimple action(m,d,2,80);
			MotorControl::queueAction(action);
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
			MotorControl::ActionSimple action1(m,d,2,0);
			MotorControl::queueAction(action1);
		}  else if(command[0] == 'r') {
			// Left true is up
			uint8_t m[2] = {MOT_TRAL,MOT_TRAR};
			bool d[4] = {false,false};
			MotorControl::ActionSimple action(m,d,2,80);
			MotorControl::queueAction(action);
			std::this_thread::sleep_for(std::chrono::milliseconds(400));
			MotorControl::ActionSimple action1(m,d,2,0);
			MotorControl::queueAction(action1);
		} else if(command[0] == 'f') {
			uint8_t m[2] = {MOT_TRAL};
			bool d[4] = {true,true};
			MotorControl::ActionSimple action(m,d,1,40);
			MotorControl::queueAction(action);
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			MotorControl::ActionSimple action1(m,d,1,0);
			MotorControl::queueAction(action1);
		}  else if(command[0] == 'g') {
			uint8_t m[2] = {MOT_TRAL,ACT_ARMR};
			bool d[4] = {false,false};
			MotorControl::ActionSimple action(m,d,1,40);
			MotorControl::queueAction(action);
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			MotorControl::ActionSimple action1(m,d,1,0);
			MotorControl::queueAction(action1);
		}*/
	}
	return 0;
}



