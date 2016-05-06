#pragma once
#ifndef MESSAGESMOTORCONTROL_HPP_
#define MESSAGESMOTORCONTROL_HPP_

#include <Robos/MessageBase.hpp>
#include "CommonMotorDataStructures.hpp"
#include <memory>
#include <stdio.h>

namespace Messages {

struct MessageRobotControl : public Robos::MessageBase {
	MotorControl::RobotAction action;

	char * serialized;
	int len_serialized = 10;

	MessageRobotControl(char * in, int len);
	MessageRobotControl(MotorControl::RobotAction action);
	~MessageRobotControl();
};

struct MessageMotorControl : public Robos::MessageBase {
	MotorControl::MotorAction * actions;
	int numActions;

	char * serialized;
	int len_serialized;

	void serialize();

	MessageMotorControl(char * in, int len);
	MessageMotorControl(MotorControl::MotorAction * actions, int numActions);
	~MessageMotorControl();
};

} // end of namespace Messages

#endif // end of MESSAGESMOTORCONTROL_HPP_
