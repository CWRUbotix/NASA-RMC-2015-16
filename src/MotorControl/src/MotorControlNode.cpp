#include "MotorControlNode.hpp"
#include "MotorControl.hpp"
#include "MotorUtil.hpp"
#include "MessagesMotorControl.hpp"
#include "MessagesGeneral.hpp"
#include "CommonMotorDataStructures.hpp"
#include <memory>

namespace MotorControl {

MotorNode::MotorNode() : Robos::NodeBase("MotorControlNode", "MotorScheduler",
                                         std::vector<std::string>{"RobotControl","MotorControl"},
                                         Async::Types::JobPriority::IMMEDIATE) {}

Robos::MessageBasePtr MotorNode::MainCallbackImpl(Robos::MessageBasePtr pMessage) {
	std::shared_ptr<Robos::MessageBase> r;
	if(pMessage->topic == "MotorAction") {
		std::shared_ptr<Messages::MessageMotorAction> message = std::static_pointer_cast<Messages::MessageMotorAction>(pMessage);
		queueAction(message->action);
		// Respond
	}
	return r;
}
MotorNode::~MotorNode() {}

} // end of namespace MotorControl
