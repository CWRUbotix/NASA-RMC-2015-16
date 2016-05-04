#include <MotorControlNode.hpp>
#include "MessagesMotorControl.hpp"
#include <memory>

namespace MotorControl {
MotorNode::MotorNode() : Robos::NodeBase("MotorControlNode", "MotorScheduler", std::vector<std::string>{"RobotControl","MotorControl"}, Async::Types::JobPriority::IMMEDIATE) {

}
MotorNode::~MotorNode() {

}
Robos::MessageBasePtr MotorNode::MainCallbackImpl(Robos::MessageBasePtr pMessage) {
	switch(pMessage->topic) {
	case "RobotControl":
		std::shared_ptr<Messages::MessageRobotControl> message1 = (std::shared_ptr<Messages::MessageRobotControl>)pMessage;
		execute(message1->action);
		return Messages::MessageSuccess();
	case "MotorControl":
		std::shared_ptr<Messages::MessageMotorControl> message2 = (std::shared_ptr<Messages::MessageMotorControl>)pMessage;
		execute(message2->actions,message2->numActions);
		return Messages::MessageSuccess();
	default:
		return Messages::MessageFailure();
	}
}
}
