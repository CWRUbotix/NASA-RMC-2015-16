#pragma once
#include <map>
#ifndef MOTORUTIL_HPP_
#define MOTORUTIL_HPP_

namespace MotorControl {

#define	MOT_FR		0x00
#define	MOT_FL		0x01
#define	MOT_BR		0x02
#define	MOT_BL		0x03
#define MOT_TRAL	0x04
#define MOT_TRAR	0x05
#define MOT_CBUC	0x06
#define MOT_CHOP	0x07
#define	ACT_WHEL	0x08
#define	ACT_WHER	0x09
#define ACT_ARML	0x0A
#define ACT_ARMR	0x0B

#define SCMD_WHOIS	0x80	// Whois command
#define SCMD_MOT	0x81	// Motor control command
#define SCMD_ST		0x82	// Motor status command


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


std::map<char, double> maxSpeeds; // Maximum speeds (rad/s)
std::map<char, double> maxCurrents; // Maximum currents
std::map<char, long> ctRevs; // Counts per rev
char scaleVelocity(char motor, double val);
char scaleCurrent(char motor, double val);
char scaleChar(double val, double max, char max_c);

// From steps/second to velocity
double convertVelocity(char motor, int val);
// Unscale from char
double unscaleVelocity(char motor, char val);
double unscaleCurrent(char motor, char val);

void initializeMaximums();

} // end of namespace MotorControl

#endif // end of MOTORUTIL_HPP_
