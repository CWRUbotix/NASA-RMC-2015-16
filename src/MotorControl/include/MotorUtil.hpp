#pragma once
#ifndef MOTORUTIL_HPP_
#define MOTORUTIL_HPP_

#include <map>
#include "CommonMotorDataStructures.hpp"

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
#define	ACT_L		0x08
#define	ACT_R		0x09
#define ACT_ARML	0x0A
#define ACT_ARMR	0x0B

#define	CMD_FWD		0x80
#define	CMD_BWD		0x81
#define	CMD_TL		0x82
#define	CMD_TR		0x83
#define	CMD_OW		0x84
#define CMD_CW		0x85
#define	CMD_INDV	0x86
#define CMD_TLTD	0x87
#define CMD_TLTU	0x88
#define CMD_TRAD	0x89
#define CMD_TRAU	0x8A
#define CMD_BF		0x8B
#define CMD_BB		0x8C
#define CMD_STATUS	0x8D

struct MotorStatus {
	char motor;
	double speed, voltage, current;
};

std::map<char, double> maxDistances;
std::map<char, double> maxSpeeds;
char scaleDistance(char motor, double val);
char scaleVelocity(char motor, double val);

} // end of namespace MotorControl

#endif // end of MOTORUTIL_HPP_
