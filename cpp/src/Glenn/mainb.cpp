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
	/*
	if (argc != 2)
	{
		printf("Please enter the IP address of the control station.\n");
		exit(-1);
	}
	
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
	std::string filep = "/dev/" + files.front();
	const char* c = filep.c_str();*/
	MotorControl::initialize("/dev/ttyACM0");
	sleep(1);

	//initialize_client(5005, 100, argv[0]);

	printf("Start listening.\n");

	while(1) {
		printf("Please enter a command.\n");

		std::string rcvd_command;

		std::getline(std::cin, rcvd_command);

		/*
		char command[2];
		char sp_ptr[3];
		scanf("%s %s", command, sp_ptr);
		char c;
		while((c = getchar()) != '\n' && c != EOF);
		*/
		
		//get_command(rcvd_command);
		//printf("%s\n", rcvd_command);
		//send_reply ((char *)"msg rcvd\n", strlen("msg rcvd\n") + 1);

		std::string command_string;
		std::string speed_command;
		size_t pos = 0;
		std::string delimiter = " ";
		pos = rcvd_command.find(delimiter);
		command_string = rcvd_command.substr(0, pos);
		rcvd_command.erase(0, pos + delimiter.length());
		pos = rcvd_command.find(delimiter);
		speed_command = rcvd_command.substr(0, pos);
		rcvd_command.erase(0, pos + delimiter.length());

		//const char* command = commands[0].c_str();

		int speed = 0;
		if (!speed_command.empty()) 
			speed = atoi(speed_command.c_str());
		if (speed < 0)
			speed = 0;
		else if (speed > 125)
			speed = 125;

		const char* command = command_string.c_str();

		if(command[0] == 'o') {
			uint8_t m[12] = {MOT_FR,MOT_FL,MOT_BR,MOT_BL,MOT_TRAL,MOT_TRAR,MOT_CBUC,MOT_CHOP,ACT_WHEL,ACT_WHER,ACT_ARML,ACT_ARML};
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
			if (speed_command.empty())
				speed = 100;
			MotorControl::ActionSimple action(m,d,4,speed);
			MotorControl::queueAction(action);
		} else if(command[0] == 's') {
			uint8_t m[4] = {MOT_FR,MOT_FL,MOT_BR,MOT_BL};
			bool d[4] = {true,false,true,false};
			if (speed_command.empty())
				speed = 100;
			MotorControl::ActionSimple action(m,d,4,speed);
			MotorControl::queueAction(action);
		} else if(command[0] == 'd') {
			uint8_t m[4] = {MOT_FR,MOT_FL,MOT_BR,MOT_BL};
			bool d[4] = {true,true,true,true};
			if (speed_command.empty())
				speed = 100;
			MotorControl::ActionSimple action(m,d,4,speed);
			MotorControl::queueAction(action);
		} else if(command[0] == 'a') {
			uint8_t m[4] = {MOT_FR,MOT_FL,MOT_BR,MOT_BL};
			bool d[4] = {false,false,false,false};
			if (speed_command.empty())
				speed = 100;
			MotorControl::ActionSimple action(m,d,4,speed);
			MotorControl::queueAction(action);
		} else if(command[0] == 'e') {
			uint8_t m[2] = {MOT_TRAL,MOT_TRAR};
			bool d[4] = {true,true};
			if (speed_command.empty())
				speed = 40;
			MotorControl::ActionSimple action(m,d,2,speed);
			MotorControl::queueAction(action);
		} else if(command[0] == 'r') {
			uint8_t m[2] = {MOT_TRAL,MOT_TRAR};
			bool d[4] = {false,false};
			if (speed_command.empty())
				speed = 40;
			MotorControl::ActionSimple action(m,d,2,speed);
			MotorControl::queueAction(action);
		} else if(command[0] == 'q') {
			uint8_t m[2] = {MOT_TRAL,MOT_TRAR};
			bool d[4] = {false,false};
			MotorControl::ActionSimple action(m,d,2,0);
			MotorControl::queueAction(action);
		} else if(command[0] == 'x') {
			uint8_t m[1] = {MOT_CBUC};
			bool d[4] = {true};
			if (speed_command.empty())
				speed = 100;
			MotorControl::ActionSimple action(m,d,1,speed);
			MotorControl::queueAction(action);
		} else if(command[0] == 'v') {
			uint8_t m[1] = {MOT_CHOP};
			bool d[4] = {false};
			if (speed_command.empty())
				speed = 40;
			MotorControl::ActionSimple action(m,d,1,speed);
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



