#pragma once
#ifndef COMMONDATASTRUCTURES_COMMONMOTORDATASTRUCTURES_HPP
#define COMMONDATASTRUCTURES_COMMONMOTORDATASTRUCTURES_HPP

// SYSTEM INCLUDES


// C++ PROJECT INCLUDES


namespace MotorControl
{

struct MotorAction {
	char motor;
	double speed, distance;
	bool ovr;
};

struct RobotAction {
	char command;
	double speed, distance;
	bool ovr;
};

} // end of namespace MotorControl

#endif // end of COMMONDATASTRUCTURES_COMMONMOTORDATASTRUCTURES_HPP
