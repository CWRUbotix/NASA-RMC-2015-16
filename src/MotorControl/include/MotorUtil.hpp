#pragma once
#include <map>
#include "CommonMotorDataStructures.hpp"
#ifndef MOTORUTIL_HPP_
#define MOTORUTIL_HPP_

namespace MotorControl {

#define RAMP_EXP	0x00
#define RAMP_LIN	0x01

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

#define	CMD_FWD		0x00	// Forward
#define	CMD_BWD		0x01	// Backward
#define	CMD_TL		0x02	// Turn left
#define	CMD_TR		0x03	// Turn right
#define	CMD_OW		0x04	// Open wheels
#define CMD_CW		0x05	// Close wheels
#define	CMD_INDV	0x06	// Individual control
#define CMD_TLTD	0x07	// Tilt arm down
#define CMD_TLTU	0x08	// Tilt arm up
#define CMD_TRAD	0x09	// Translate arm down
#define CMD_TRAU	0x0A	// Translate arm up
#define CMD_BF		0x0B	// Buckets forward
#define CMD_BB		0x0C	// Buckets backward
#define CMD_HF		0x0D	// Hopper out
#define CMD_HB		0x0E	// Hopper in
#define CMD_STATUS	0x0F	// Motor status

#define SCMD_WHOIS	0x80	// Whois command
#define SCMD_MOT	0x81	// Motor control command
#define SCMD_ST		0x82	// Motor status command

struct MotorStatus {
	char motor;
	double speed, voltage, current;
};

extern std::map<char, double> maxDistances;
extern std::map<char, double> maxSpeeds;
char scaleDistance(char motor, double val);
char scaleVelocity(char motor, double val);

} // end of namespace MotorControl

#endif // end of MOTORUTIL_HPP_
