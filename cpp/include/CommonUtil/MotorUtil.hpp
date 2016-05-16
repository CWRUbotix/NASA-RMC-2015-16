/*
 * MotorUtil.hpp
 *
 *  Created on: May 9, 2016
 *      Author: root
 */
#include <memory>
#include <string.h>
#include <map>
#include <stdlib.h>
//#include "Messages/MessagesMotorControl.hpp"

#ifndef MOTORUTIL_HPP_
#define MOTORUTIL_HPP_

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

#define STAT_ACTION_NONE	0x00
#define STAT_ACTION_QUEUE	0x01
#define STAT_ACTION_TORUN	0x02
#define STAT_ACTION_NORUN	0x03
#define STAT_ACTION_RUN		0x04
#define STAT_ACTION_FAIL	0x05
#define STAT_ACTION_OVR		0x06
#define STAT_ACTION_DONE	0x07

namespace MotorControl
{
extern std::map<char, double> maxSpeeds; // Maximum speeds (rad/s)
extern std::map<char, double> maxCurrents; // Maximum currents
extern std::map<char, long> ctRevs;// Counts per rev
char scaleVelocity(char motor, double val);
char scaleCurrent(char motor, double val);
char scaleChar(double val, double max, char max_c);

// One speed, many motors
// Can handle both individual motor control and robot control
struct Action {
	char* motor;
	bool* direction;
	double speed, speed_rt, distance, distance_remaining;
	bool ovr, use_dist;
	char status;
	long id;
	char num_motors;

	char * serialized;
	int len_serialized;

	Action(char* m,bool* dr,char n,double s,double d,bool o,bool ds);
	Action(char* m,bool* dr,char n,double s,bool o);
	Action(char * s, int n);
	Action();
	~Action();
};

// Power is averaged over n seconds
struct Status {
	double speed_inst, power_inst, speed_avg, power_avg;
};

// From steps/second to velocity
double convertVelocity(char motor, int val);
// Unscale from char
double unscaleVelocity(char motor, char val);
double unscaleCurrent(char motor, char val);

void initializeMaximums();

Action forward(double speed, bool ovr);
Action forward(double speed, double dist, bool ovr);
Action backward(double speed, bool ovr);
Action backward(double speed, double dist, bool ovr);
Action turnLeft(double speed, bool ovr);
Action turnLeft(double speed, double angle, bool ovr);
Action turnRight(double speed, bool ovr);
Action turnRight(double speed, double angle, bool ovr);
Action openWheels(bool ovr);
Action closeWheels(bool ovr);
Action tiltArmDown(double speed, double angle);
Action tiltArmUp(double speed, double andgle);
Action translateArmDown(double speed, double distance);
Action translateArmDown(double speed);
Action translateArmUp(double speed, double distance);
Action translateArmUp(double speed);
Action bucketForward(double speed);
Action bucketBackward(double speed);
Action hopperOut(double speed);
Action hopperOut(double speed, double dist);
Action hopperIn(double speed);
Action hopperIn(double speed, double dist);

} // end of namespace MotorControl

#endif /* MOTORUTIL_HPP_ */
