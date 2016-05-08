#ifndef MOTORCONTROL_HPP_
#define MOTORCONTROL_HPP_

#include "MotorUtil.hpp"
#include "USBSerial.hpp"
#include <map>

namespace MotorControl {

void forward(double speed, bool ovr);
void forward(double speed, double dist, bool ovr);
void backward(double speed, bool ovr);
void backward(double speed, double dist, bool ovr);
void turnLeft(double speed, bool ovr);
void turnLeft(double speed, double angle, bool ovr);
void turnRight(double speed, bool ovr);
void turnRight(double speed, double angle, bool ovr);
void openWheels(bool ovr);
void closeWheels(bool ovr);
void tiltArmDown(double speed, double angle);
void tiltArmUp(double speed, double andgle);
void translateArmDown(double speed, double distance);
void translateArmDown(double speed);
void translateArmUp(double speed, double distance);
void translateArmUp(double speed);
void bucketForward(double speed);
void bucketBackward(double speed);
void hopperOut(double speed);
void hopperOut(double speed, double dist);
void hopperIn(double speed);
void hopperIn(double speed, double dist);

void setRampType(char type, double factor);

USBSerial::Port port("");

int initialize(char * device);
void execute(RobotAction action);
void execute(MotorAction * actions, int numActions);
MotorStatus getMotorStatus(char motor);
std::map<char, MotorStatus> getMotorStatuses();

} // end of namespace MotorControl

#endif // end of MOTORCONTROL_HPP_
