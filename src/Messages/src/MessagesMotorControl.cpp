#include "MessagesMotorControl.hpp"

namespace Messages {

MessageRobotControl::MessageRobotControl(char * in, int len, Network::Response rsp) :
		MessageBaseCommand(rsp,"RobotControl") {
	if(len != len_serialized) {
		::perror("Invalid serialized Robot Control message");
	}
	serialized = in;
	double speed = 0;
	double distance = 0;
	::memcpy(&speed,in+1,sizeof(double));
	::memcpy(&distance,in+1+sizeof(double),sizeof(double));
	action.command = in[0];
	action.speed = speed;
	action.distance = distance;
	action.ovr = (bool) in[9];
}

MessageRobotControl::MessageRobotControl(MotorControl::RobotAction action, Network::Response rsp) :
    MessageBaseCommand(rsp,"RobotControl"), action(action) {
	serialized = (char*)::malloc(len_serialized);
	serialized[0] = action.command;
	::memcpy(serialized+1,&action.speed,sizeof(double));
	::memcpy(serialized+1+sizeof(double),&action.distance,sizeof(double));
	serialized[9] = (char)action.ovr;
}

MessageRobotControl::~MessageRobotControl() {}


MessageMotorControl::MessageMotorControl(MotorControl::MotorAction * actions, int numActions, Network::Response rsp) :
    MessageBaseCommand(rsp,"MotorControl"), actions(actions), numActions(numActions) {
	len_serialized = numActions * 10;
	serialized = (char*)::malloc(len_serialized);
	for(int i = 0; i < numActions; i++) {
		serialized[i*10] = actions[i].motor;
		::memcpy(serialized+(i*10+1),&actions[i].speed,sizeof(double));
		::memcpy(serialized+(i*10+5),&actions[i].distance,sizeof(double));
		serialized[i*10+9] = (char)actions[i].ovr;
	}
}

MessageMotorControl::MessageMotorControl(char * in, int len, Network::Response rsp) :
    	    MessageBaseCommand(rsp,"MotorControl") {
	if(len % 10 != 0) {
		::perror("Invalid serialized Robot Control message");
	}
	numActions = len/10;
	actions = (MotorControl::MotorAction*)::malloc(sizeof(MotorControl::MotorAction)*numActions);
	len_serialized = len;
	serialized = in;
	for(int i = 0; i < numActions; i++) {
		actions[i].motor = in[i*10];
		::memcpy(&actions[i].speed,in+(i*10+1),sizeof(double));
		::memcpy(&actions[i].distance,in+(i*10+5),sizeof(double));
		actions[i].ovr = (bool)in[i*10+9];
	}
}

MessageMotorControl::~MessageMotorControl() {}

} // end of namespace Messages
