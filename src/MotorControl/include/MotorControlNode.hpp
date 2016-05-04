#include "Robos/NodeBase.hpp"
#include "Robos/MessageBase.hpp"
#ifndef MOTORCONTROLNODE_HPP_
#define MOTORCONTROLNODE_HPP_

namespace MotorControl {
class MotorNode : public Robos::NodeBase {
private:
	void MainCallbackImpl(Robos::MessageBasePtr pMessage) override;
public:
	MotorNode();
	~MotorNode();
};
}

#endif
