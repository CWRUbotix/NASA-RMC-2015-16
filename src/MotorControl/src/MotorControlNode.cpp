#include <MotorControlNode.hpp>

namespace MotorControl {
MotorNode::MotorNode() : Robos::NodeBase("MotorControlNode", "MotorScheduler", std::vector<std::string>{"ManualControl"}, Async::Types::JobPriority::IMMEDIATE) {

}
MotorNode::~MotorNode() {

}
Robos::MessageBasePtr MotorNode::MainCallbackImpl(Robos::MessageBasePtr pMessage) {

}
}
