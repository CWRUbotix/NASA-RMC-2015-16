#include <MotorControl.hpp>
#include <I2C.hpp>

namespace MotorControl {

void execute(RobotAction action) {
	I2C::setSlaveAddress(I2C::ADDRESSS_MOTORS);
	int len = 2;
	char * buffer;
	if(action.distance != 0) {
		len = 3;
		buffer = {scaleToChar(action.speed,maxSpeeds.find(action.command)->second),
				  scaleToChar(action.distance,maxDistances.find(action.command)->second),
				  (char)action.ovr};
	} else {
		buffer = {scaleToChar(action.speed,maxSpeeds.find(action.command)->second),
				  (char)action.ovr};	}
	I2C::sendCommand(action.command,buffer,len);
}

void setMotors(MotorAction * actions, int numActions) {
	I2C::setSlaveAddress(I2C::ADDRESSS_MOTORS);
	char * buffer = malloc(numActions*4);
	for(int i = 0; i < numActions; i++) {
		buffer[i*4] = actions[i].motor;
		buffer[i*4+1] = scaleToChar(actions[i].speed,maxSpeeds.find(actions[i].motor)->second);
		buffer[i*4+2] = scaleToChar(actions[i].distance,maxDistances.find(actions[i].motor)->second);
		buffer[i*4+3] = (char)actions[i].ovr;
	}
	I2C::sendCommand(CMD_INDV,buffer, numActions*4);
}

}
