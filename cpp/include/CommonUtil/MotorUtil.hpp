/*
 * MotorUtil.hpp
 *
 *  Created on: May 9, 2016
 *      Author: root
 */
#include <memory>
#include <string.h>
#include <map>

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
std::map<char, double> maxSpeeds; // Maximum speeds (rad/s)
std::map<char, double> maxCurrents; // Maximum currents
std::map<char, long> ctRevs; // Counts per rev
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
	char status = STAT_ACTION_NONE;
	long id = 0;
	char num_motors;

	char * serialized;
	int len_serialized;

	Action(char* m,bool* dr,char n,double s,double d,bool o,bool ds) {
		motor = m;
		direction = dr;
		speed = s;
		speed_rt = s;
		distance = d;
		distance_remaining = d;
		ovr = o;
		use_dist = ds;
		num_motors = n;
		len_serialized = n*2 + 11;
		serialized = (char*) ::malloc(len_serialized);
		serialized[0] = n;
		::memcpy(serialized+1,&s,4);
		::memcpy(serialized+5,&d,4);
		serialized[9] = (char) o;
		serialized[10] = (char) ds;
		::memcpy(serialized+11,m,n);
		::memcpy(serialized+11+n,(char*)dr,n);
	};
	Action(char* m,bool* dr,char n,double s,bool o) : Action(m,dr,n,s,0,o,false) {

	};
	Action(char * s, int n) {
		num_motors = s[0];
		::memcpy(&speed,s+1,4);
		speed_rt = speed;
		::memcpy(&distance,s+5,4);
		distance_remaining = distance;
		ovr = (bool)s[9];
		use_dist = (bool)s[10];
		motor = (char*) malloc(num_motors);
		::memcpy(s+11,motor,num_motors);
		direction = (bool*) malloc(num_motors);
		::memcpy(s+11+num_motors,direction,num_motors);
		serialized = s;
		len_serialized = n;
	}
	Action() : Action(NULL,NULL,0,0,0,false,false) {}
	~Action();
};

// Power is averaged over n seconds
struct Status {
	double speed_inst, power_inst, speed_avg, power_avg;
	Status(double,double);
};

// From steps/second to velocity
double convertVelocity(char motor, int val);
// Unscale from char
double unscaleVelocity(char motor, char val);
double unscaleCurrent(char motor, char val);

void initializeMaximums();

} // end of namespace MotorControl

#endif /* MOTORUTIL_HPP_ */
