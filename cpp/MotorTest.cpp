/*
 * MotorTest.cpp
 *
 *  Created on: May 10, 2016
 *      Author: root
 */

#include "MotorControl/MotorControl.hpp"
#include "CommonUtil/MotorUtil.hpp"
#include <thread>
#include <unistd.h>
#include <chrono>

#include <ctime>
int main() {
	MotorControl::initialize("/dev/ttyACM0");
	sleep(1);
	char m[4] = {MOT_FR,MOT_FL,MOT_BR,MOT_BL};
	bool di[4] = {true,true,true,true};
	MotorControl::Action action(m,di,4,1,true);
	MotorControl::queueAction(action);
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	MotorControl::halt();
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	return 0;
}
