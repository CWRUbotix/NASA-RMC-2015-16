#include "MotorControl.hpp"
#include "MotorUtil.hpp"
#include "CommonMotorDataStructures.hpp"
#include "I2C.hpp"
#include <stdio.h>

namespace MotorControl {

int initialize(char * device) {
	USBSerial::Port port(device);
	if(port.open() < 0) {
		::perror("Failed to start Motor Control");
	}
	return 0;
}

void execute(RobotAction action) {
	int len = 3;
	char * buffer = (char*)malloc(3);
	buffer[0] = scaleVelocity(action.command,action.speed);
	buffer[1] = scaleDistance(action.command,action.distance);
	buffer[2] = (char)action.ovr;
	port.write(buffer, len);
}

void execute(MotorAction * actions, int numActions) {
	int len = numActions*4;
	char * buffer = (char*)malloc(len);
	for(int i = 0; i < numActions; i++) {
		buffer[i*4] = actions[i].motor;
		buffer[i*4+1] = scaleVelocity(actions[i].motor,actions[i].speed);
		buffer[i*4+2] = scaleDistance(actions[i].motor,actions[i].distance);
		buffer[i*4+3] = (char)actions[i].ovr;
	}
	port.write(buffer,len);
}

} // end of namespace MotorControl
