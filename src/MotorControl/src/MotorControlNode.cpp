#include <MotorControlNode.hpp>
#include "MotorControl.hpp"
#include "MessagesMotorControl.hpp"
#include "MessagesGeneral.hpp"
#include <memory>

namespace MotorControl {
MotorNode::MotorNode() : Robos::NodeBase("MotorControlNode", "MotorScheduler", std::vector<std::string>{"RobotControl","MotorControl"}, Async::Types::JobPriority::IMMEDIATE) {

}
MotorNode::~MotorNode() {

}
Robos::MessageBasePtr MotorNode::MainCallbackImpl(Robos::MessageBasePtr pMessage) {
	if(pMessage->topic == "RobotControl") {
		std::shared_ptr<Messages::MessageRobotControl> message = std::static_pointer_cast<Messages::MessageRobotControl>(pMessage);
		execute(message->action);
		std::shared_ptr<Messages::MessageSuccess> r = std::make_shared<Messages::MessageSuccess>(Messages::MessageSuccess());
		return r;
	} else if(pMessage->topic == "MotorControl") {
		std::shared_ptr<Messages::MessageMotorControl> message = std::static_pointer_cast<Messages::MessageMotorControl>(pMessage);
		execute(message->actions,message->numActions);
		std::shared_ptr<Messages::MessageSuccess> r = std::make_shared<Messages::MessageSuccess>(Messages::MessageSuccess());
		return r;
	}
	std::shared_ptr<Messages::MessageFailure> r = std::make_shared<Messages::MessageFailure>(Messages::MessageFailure());
	return r;
}
}
