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

#include <vector>
#include <string>
#include <dirent.h>
#include <iostream>
#include <stdio.h>

int main(int argc, char** argv) {
	std::vector<std::string> files = std::vector<std::string>();
	DIR* dp = opendir("/dev/");
	struct dirent* dirp;
	std::string file;
	while((dirp = readdir(dp)) != NULL) {
		file = std::string(dirp->d_name);
		if(!file.substr(0,6).compare("ttyACM")) {
			files.push_back(std::string(dirp->d_name));
		}
	}
	closedir(dp);

	if(!files.size()) {
		printf("Arduino is not connected");
		return -1;
	}
	std::string file = "/dev/" + files.front();
	char* c = file.c_str();
	MotorControl::initialize(c);
	sleep(1);
	printf("Start listening.\n");
	char command[MAX_RECV_LEN];

	while(1) {
		printf("Please enter a command.\n");
		scanf("%s", command);

		if(command[0] == 'o') {
			uint8_t m[4] = {MOT_FR,MOT_FL,MOT_BR,MOT_BL,MOT_TRAL,MOT_TRAR,MOT_CBUC,MOT_CHOP,ACT_WHEL,ACT_WHER,ACT_ARML,ACT_ARML};
			bool d[12];
			MotorControl::ActionSimple action(m,d,12,0);
			MotorControl::queueAction(action);
		} else if(command[0] == 'p') {
			uint8_t m[4] = {MOT_FR,MOT_FL,MOT_BR,MOT_BL};
			bool d[4] = {false,true,false,true};
			MotorControl::ActionSimple action(m,d,4,0);
			MotorControl::queueAction(action);
		} else if(command[0] == 'w') {
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
	}
	return 0;
}



