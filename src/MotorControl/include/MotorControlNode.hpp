#include "Robos/NodeBase.hpp"
#include "Robos/MessageBase.hpp"
#include "MessagesMotorControl.hpp"
#ifndef MOTORCONTROLNODE_HPP_
#define MOTORCONTROLNODE_HPP_

namespace MotorControl {
class MotorNode : public Robos::NodeBase {
private:
	Robos::MessageBasePtr MainCallbackImpl(Robos::MessageBasePtr pMessage) override;
public:
	MotorNode();
	~MotorNode();
};
}

#endif
