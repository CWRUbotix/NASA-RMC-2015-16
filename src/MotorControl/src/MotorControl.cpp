#include "MotorControl.hpp"
#include "MotorUtil.hpp"
#include "CommonMotorDataStructures.hpp"
#include "I2C.hpp"

namespace MotorControl {

void execute(RobotAction action) {
	I2C::I2C::setAddress(0x80);
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
	I2C::I2C::sendPacket(buffer,len);
}

void execute(MotorAction * actions, int numActions) {
	I2C::I2C::setAddress(0x80);
	char * buffer = (char*)malloc(numActions*4);
	for(int i = 0; i < numActions; i++) {
		buffer[i*4] = actions[i].motor;
		buffer[i*4+1] = scaleVelocity(actions[i].motor,actions[i].speed);
		buffer[i*4+2] = scaleDistance(actions[i].motor,actions[i].distance);
		buffer[i*4+3] = (char)actions[i].ovr;
	}
	I2C::I2C::sendPacket(buffer,numActions*4);
}

} // end of namespace MotorControl
