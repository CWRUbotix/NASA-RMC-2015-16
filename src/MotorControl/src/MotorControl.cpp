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
	int len = 0;
	switch(action.command) {
	case CMD_FWD:
		len = 4;
		m = (MotorAction*)::malloc(sizeof(MotorAction)*4);
		m[0] = MotorAction(MOT_FR,speed,dist,action.ovr);
		m[1] = MotorAction(MOT_FL,speed,dist,action.ovr);
		m[2] = MotorAction(MOT_BR,speed,dist,action.ovr);
		m[3] = MotorAction(MOT_BL,speed,dist,action.ovr);
		break;
	case CMD_BWD:
		len = 4;
		m = (MotorAction*)::malloc(sizeof(MotorAction)*4);
		m[0] = MotorAction(MOT_FR,-speed,dist,action.ovr);
		m[1] = MotorAction(MOT_FL,-speed,dist,action.ovr);
		m[2] = MotorAction(MOT_BR,-speed,dist,action.ovr);
		m[3] = MotorAction(MOT_BL,-speed,dist,action.ovr);
		break;
	case CMD_TL:
		len = 4;
		m = (MotorAction*)::malloc(sizeof(MotorAction)*4);
		m[0] = MotorAction(MOT_FR,speed,dist,action.ovr);
		m[1] = MotorAction(MOT_FL,-speed,dist,action.ovr);
		m[2] = MotorAction(MOT_BR,speed,dist,action.ovr);
		m[3] = MotorAction(MOT_BL,-speed,dist,action.ovr);
		break;
	case CMD_TR:
		len = 4;
		m = (MotorAction*)::malloc(sizeof(MotorAction)*4);
		m[0] = MotorAction(MOT_FR,-speed,dist,action.ovr);
		m[1] = MotorAction(MOT_FL,speed,dist,action.ovr);
		m[2] = MotorAction(MOT_BR,-speed,dist,action.ovr);
		m[3] = MotorAction(MOT_BL,speed,dist,action.ovr);
		break;
	case CMD_OW:
		len = 2;
		m = (MotorAction*)::malloc(sizeof(MotorAction)*2);
		m[0] = MotorAction(ACT_WHEL,speed,dist,action.ovr);
		m[1] = MotorAction(ACT_WHER,speed,dist,action.ovr);
		break;
	case CMD_CW:
		len = 2;
		m = (MotorAction*)::malloc(sizeof(MotorAction)*2);
		m[0] = MotorAction(ACT_WHEL,-speed,dist,action.ovr);
		m[1] = MotorAction(ACT_WHER,-speed,dist,action.ovr);
		break;
	case CMD_INDV:
		break;
	case CMD_TLTD:
		len = 2;
		m = (MotorAction*)::malloc(sizeof(MotorAction)*2);
		m[0] = MotorAction(ACT_ARML,speed,dist,action.ovr);
		m[1] = MotorAction(ACT_ARMR,speed,dist,action.ovr);
		break;
	case CMD_TLTU:
		len = 2;
		m = (MotorAction*)::malloc(sizeof(MotorAction)*2);
		m[0] = MotorAction(ACT_ARML,-speed,dist,action.ovr);
		m[1] = MotorAction(ACT_ARMR,-speed,dist,action.ovr);
		break;
	case CMD_TRAD:
		len = 2;
		m = (MotorAction*)::malloc(sizeof(MotorAction)*2);
		m[0] = MotorAction(MOT_TRAL,speed,dist,action.ovr);
		m[1] = MotorAction(MOT_TRAL,speed,dist,action.ovr);
		break;
	case CMD_TRAU:
		len = 2;
		m = (MotorAction*)::malloc(sizeof(MotorAction)*2);
		m[0] = MotorAction(MOT_TRAL,-speed,dist,action.ovr);
		m[1] = MotorAction(MOT_TRAL,-speed,dist,action.ovr);
		break;
	case CMD_BF:
		len = 1;
		m = (MotorAction*)::malloc(sizeof(MotorAction));
		m[0] = MotorAction(MOT_CBUC,speed,dist,action.ovr);
		break;
	case CMD_BB:
		len = 1;
		m = (MotorAction*)::malloc(sizeof(MotorAction));
		m[0] = MotorAction(MOT_CBUC,-speed,dist,action.ovr);
		break;
	case CMD_HF:
		len = 1;
		m = (MotorAction*)::malloc(sizeof(MotorAction));
		m[0] = MotorAction(MOT_CHOP,speed,dist,action.ovr);
		break;
	case CMD_HB:
		len = 1;
		m = (MotorAction*)::malloc(sizeof(MotorAction));
		m[0] = MotorAction(MOT_CHOP,-speed,dist,action.ovr);
		break;
	case CMD_STATUS:

		break;
	}
	execute(m,len);
}

void execute(MotorAction * actions, int numActions) {
	int len = numActions*2;
	char * buffer = (char*)malloc(len);
	for(int i = 0; i < numActions; i++) {
		buffer[i*4] = actions[i].motor;
		buffer[i*4+1] = scaleVelocity(actions[i].motor,actions[i].speed);
	}
	port.write(buffer,len);
}

}
