#pragma once
#ifndef MESSAGESMOTORCONTROL_HPP_
#define MESSAGESMOTORCONTROL_HPP_

// SYSTEM INCLUDES


// C++ PROJECT INCLUDES
#include "CommonDataStructures.hpp"

namespace Messages {

struct MessageRobotControl : public Robos::MessageBase {
	MotorControl::RobotAction action;

	MessageRobotControl(MotorControl::RobotAction action);
	~MessageRobotControl();
};

struct MessageMotorControl : public Robos::MessageBase {
	std::vector<MotorControl::MotorAction> actions;
	int numActions;

	MessageMotorControl(MotorControl::MotorAction * actions, int numActions);
	~MessageMotorControl();
};

} // end of namespace Messages

#endif // end of MESSAGESMOTORCONTROL_HPP_
