#include "MotorControl/MotorControlNode.hpp"
#include "MotorControl/MotorControl.hpp"
#include "Messages/MessagesMotorControl.hpp"
#include "Messages/MessagesGeneral.hpp"
#include "CommonUtil/MotorUtil.hpp"
#include "Robos/MessageBase.hpp"
#include <memory>

namespace MotorControl {

MotorNode::MotorNode() : Robos::NodeBase("MotorControlNode", "MotorScheduler",
                                         std::vector<std::string>{"MotorAction"},
                                         Async::Types::JobPriority::IMMEDIATE) {}

Robos::MessageBasePtr MotorNode::MainCallbackImpl(Robos::MessageBasePtr pMessage) {
	std::shared_ptr<Robos:MessageBase> r;
	if(pMessage->topic == "MotorAction") {
		std::shared_ptr<Messages::MessageMotorAction> message = std::static_pointer_cast<Messages::MessageMotorAction>(pMessage);
		queueAction(message->action);
		// Respond
	}
	return r;
}
MotorNode::~MotorNode() {}

} // end of namespace MotorControl
