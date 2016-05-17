#pragma once
#ifndef MESSAGESMOTORCONTROL_HPP_
#define MESSAGESMOTORCONTROL_HPP_

#include <Robos/MessageBase.hpp>
#include "CommonUtil/MotorUtil.hpp"
#include "CommonUtil/NetworkUtil.hpp"
#include "Messages/MessagesComm.hpp"
#include <memory>
#include <stdio.h>
#include <string.h>

namespace Messages {

struct MessageMotorAction : public MessageBaseCommand {
	MotorControl::Action action;
	MessageMotorAction(MotorControl::Action action, Network::Response rsp);
	MessageMotorAction();
	~MessageMotorAction();
};

}// end of namespace Messages

#endif // end of MESSAGESMOTORCONTROL_HPP_
