#include <MessagesMotorControl.hpp>

namespace Messages {
MessageRobotControl::MessageRobotControl(MotorControl::RobotAction action) : Robos::MessageBase("RobotControl"),action(action) {}
MessageRobotControl::~MessageRobotControl(){}
MessageMotorControl::MessageMotorControl(MotorControl::MotorAction * actions, int numActions) : Robos::MessageBase("MotorControl"),actions(actions),numActions(numActions) {}
MessageMotorControl::~MessageMotorControl(){}
}
