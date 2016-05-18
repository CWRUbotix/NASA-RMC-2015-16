/*
 * main_simple.cpp
 *
 *  Created on: May 18, 2016
 *      Author: root
 */
#include <stdint.h>
#include <MotorControl/MotorControlSimple.hpp>
#include <CommonUtil/MotorUtil.hpp>

int main() {
	MotorControl::initialize("/dev/ttyACM2");
	sleep(1);
	uint8_t m[4] = {MOT_FR,MOT_FL,MOT_BR,MOT_BL};
	bool d[4] = {true,true,true,true};
	MotorControl::ActionSimple action(m,d,4,125);
	MotorControl::queueAction(action);
	sleep(1);
	uint8_t m1[4] = {MOT_BR,MOT_BL,MOT_FR,MOT_FL};
	bool d1[4] = {true,true,true,true};
	MotorControl::ActionSimple action1(m1,d1,4,125);
	MotorControl::queueAction(action1);
	sleep(1);
	MotorControl::halt();
	sleep(1);
}


