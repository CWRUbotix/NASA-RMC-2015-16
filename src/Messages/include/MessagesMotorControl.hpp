#pragma once
#ifndef MESSAGESMOTORCONTROL_HPP_
#define MESSAGESMOTORCONTROL_HPP_

#include <Robos/MessageBase.hpp>
#include "CommonMotorDataStructures.hpp"
#include <memory>
#include <stdio.h>
#include <string.h>
#include "MessagesComm.hpp"
#include "CommonCommDataStructures.hpp"

namespace Messages {

struct MessageRobotControl : public MessageBaseCommand {
	MotorControl::RobotAction action;

	char * serialized;
	int len_serialized = 10;

	MessageRobotControl(char * in, int len, Network::Response rsp);
	MessageRobotControl(MotorControl::RobotAction action, Network::Response rsp);
	~MessageRobotControl();
};

struct MessageMotorControl : public MessageBaseCommand {
	MotorControl::MotorAction * actions;
	int numActions;

	char * serialized;
	int len_serialized;

	void serialize();

	MessageMotorControl(char * in, int len, Network::Response rsp);
	MessageMotorControl(MotorControl::MotorAction * actions, int numActions, Network::Response rsp);
	~MessageMotorControl();
};

} // end of namespace Messages

#endif // end of MESSAGESMOTORCONTROL_HPP_
