#include "MotorUtil.hpp"
#ifndef MESSAGESMOTORCONTROL_HPP_
#define MESSAGESMOTORCONTROL_HPP_

namespace Messages {
struct MessageRobotControl : public Robos::MessageBase {
	MotorControl::RobotAction action;
	MessageRobotControl(MotorControl::RobotAction action);
	~MessageRobotControl();
};
struct MessageMotorControl : public Robos::MessageBase {
	MotorControl::MotorAction * actions;
	int numActions;
	MessageMotorControl(MotorControl::MotorAction * action, int numActions);
	~MessageMotorControl();
};

}

#endif
