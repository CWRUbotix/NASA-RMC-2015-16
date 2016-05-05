#pragma once
#ifndef MOTORCONTROLNODE_HPP_
#define MOTORCONTROLNODE_HPP_

#include <Robos/NodeBase.hpp>
#include <Robos/MessageBase.hpp>
#include "LibraryExport.hpp"
#include "MessagesMotorControl.hpp"

namespace MotorControl {

class MOTORCONTROLLER_API MotorNode : public Robos::NodeBase {
private:
	Robos::MessageBasePtr MainCallbackImpl(const Robos::MessageBasePtr pMessage) override;
public:
	MotorNode();
	~MotorNode();
};

} // end of namespace MotorControl

#endif // end of MOTORCONTROLNODE_HPP_
