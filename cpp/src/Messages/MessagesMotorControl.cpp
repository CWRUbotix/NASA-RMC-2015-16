/*
 * MessagesMotorControl.cpp
 *
 *  Created on: May 17, 2016
 *      Author: root
 */
#include "Messages/MessagesMotorControl.cpp"
namespace Messages {

MessageMotorAction::MessageMotorAction(MotorControl::Action action, Network::Response rsp) : MessageBaseCommand(rsp,"MotorAction"),action(action) {};
MessageMotorAction::MessageMotorAction() {};
MessageMotorAction::~MessageMotorAction() {};
}


