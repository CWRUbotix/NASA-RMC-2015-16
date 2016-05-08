#include "MotorControl.hpp"
#include "MotorUtil.hpp"
#include "CommonMotorDataStructures.hpp"
#include "I2C.hpp"
#include <stdio.h>
#include <memory>

namespace MotorControl {

int initialize(char * device) {
	USBSerial::Port port(device);
	if(port.open() < 0) {
		::perror("Failed to start Motor Control");
	}
	return 0;
}

void execute(RobotAction action) {
	char speed = scaleVelocity(action.command,action.speed);
	char dist = scaleDistance(action.command,action.speed);
	MotorAction * m;
	switch(action.command) {
	case CMD_FWD:
		m = (MotorAction*)::malloc(sizeof(MotorAction)*4);
		m[0] = MotorAction(MOT_FR,speed,dist,action.ovr);
		m[1] = MotorAction(MOT_FL,speed,dist,action.ovr);
		m[2] = MotorAction(MOT_BR,speed,dist,action.ovr);
		m[3] = MotorAction(MOT_BL,speed,dist,action.ovr);
		break;
	case CMD_BWD:
		m = (MotorAction*)::malloc(sizeof(MotorAction)*4);
		m[0] = MotorAction(MOT_FR,-speed,dist,action.ovr);
		m[1] = MotorAction(MOT_FL,-speed,dist,action.ovr);
		m[2] = MotorAction(MOT_BR,-speed,dist,action.ovr);
		m[3] = MotorAction(MOT_BL,-speed,dist,action.ovr);
		break;
	case CMD_TL:
		m = (MotorAction*)::malloc(sizeof(MotorAction)*4);
		m[0] = MotorAction(MOT_FR,speed,dist,action.ovr);
		m[1] = MotorAction(MOT_FL,-speed,dist,action.ovr);
		m[2] = MotorAction(MOT_BR,speed,dist,action.ovr);
		m[3] = MotorAction(MOT_BL,-speed,dist,action.ovr);
		break;
	case CMD_TR:
		m = (MotorAction*)::malloc(sizeof(MotorAction)*4);
		m[0] = MotorAction(MOT_FR,-speed,dist,action.ovr);
		m[1] = MotorAction(MOT_FL,speed,dist,action.ovr);
		m[2] = MotorAction(MOT_BR,-speed,dist,action.ovr);
		m[3] = MotorAction(MOT_BL,speed,dist,action.ovr);
		break;
	case CMD_OW:
		m = (MotorAction*)::malloc(sizeof(MotorAction)*2);
		m[0] = MotorAction(ACT_WHEL,speed,dist,action.ovr);
		m[1] = MotorAction(ACT_WHER,speed,dist,action.ovr);
		break;
	case CMD_CW:
		m = (MotorAction*)::malloc(sizeof(MotorAction)*2);
		m[0] = MotorAction(ACT_WHEL,-speed,dist,action.ovr);
		m[1] = MotorAction(ACT_WHER,-speed,dist,action.ovr);
		break;
	case CMD_INDV:
		break;
	case CMD_TLTD:
		m = (MotorAction*)::malloc(sizeof(MotorAction)*2);
		m[0] = MotorAction(ACT_ARML,speed,dist,action.ovr);
		m[1] = MotorAction(ACT_ARMR,speed,dist,action.ovr);
		break;
	case CMD_TLTU:
		m = (MotorAction*)::malloc(sizeof(MotorAction)*2);
		m[0] = MotorAction(ACT_ARML,-speed,dist,action.ovr);
		m[1] = MotorAction(ACT_ARMR,-speed,dist,action.ovr);
		break;
	case CMD_TRAD:
		m = (MotorAction*)::malloc(sizeof(MotorAction)*2);
		m[0] = MotorAction(MOT_TRAL,speed,dist,action.ovr);
		m[1] = MotorAction(MOT_TRAL,speed,dist,action.ovr);
		break;
	case CMD_TRAU:
		m = (MotorAction*)::malloc(sizeof(MotorAction)*2);
		m[0] = MotorAction(MOT_TRAL,-speed,dist,action.ovr);
		m[1] = MotorAction(MOT_TRAL,-speed,dist,action.ovr);
		break;
	case CMD_BF:
		m = (MotorAction*)::malloc(sizeof(MotorAction));
		m[0] = MotorAction(MOT_CBUC,speed,dist,action.ovr);
		break;
	case CMD_BB:
		m = (MotorAction*)::malloc(sizeof(MotorAction));
		m[0] = MotorAction(MOT_CBUC,-speed,dist,action.ovr);
		break;
	case CMD_STATUS:

		break;
	}
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
