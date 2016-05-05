#include "MotorControl.hpp"
#include <I2C/I2C.hpp>

namespace MotorControl {

void execute(RobotAction action) {
	I2C::setAddress(I2C::ADDRESSS_MOTORS);
	int len = 2;
	char * buffer;
	if(action.distance != 0) {
		len = 3;
		buffer = (char*)malloc(3);
		buffer[0] = scaleVelocity(action.command,action.speed);
		buffer[1] = scaleDistance(action.command,action.distance);
		buffer[2] = (char)action.ovr;
	} else {
		buffer = (char*)malloc(2);
		buffer[0] = scaleVelocity(action.command,action.speed);
		buffer[1] = (char)action.ovr;
	}
	I2C::sendPacket(action.command,buffer,len);
}

void execute(MotorAction * actions, int numActions) {
	I2C::setAddress(I2C::ADDRESSS_MOTORS);
	char * buffer = (char*)malloc(numActions*4);
	for(int i = 0; i < numActions; i++) {
		buffer[i*4] = actions[i].motor;
		buffer[i*4+1] = scaleVelocity(actions[i].motor,actions[i].speed);
		buffer[i*4+2] = scaleDistance(actions[i].motor,actions[i].distance);
		buffer[i*4+3] = (char)actions[i].ovr;
	}
	I2C::sendPacket(CMD_INDV,buffer, numActions*4);
}

} // end of namespace MotorControl
