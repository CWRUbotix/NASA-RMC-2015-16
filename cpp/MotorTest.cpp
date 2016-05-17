/*
 * MotorTest.cpp
 *
 *  Created on: May 10, 2016
 *      Author: root
 */

#include "MotorControl/MotorControl.hpp"
#include "CommonUtil/MotorUtil.hpp"
#include "USBSerial/USBSerial.hpp"
#include <thread>
#include <unistd.h>
#include <chrono>

#include <ctime>
int main() {
	MotorControl::initialize("/dev/ttyACM2");
	sleep(1);
	char m[1] = {MOT_FR};
	bool di[1] = {true};
	MotorControl::Action action(m,di,1,2.5,true);
	MotorControl::queueAction(action);
	std::this_thread::sleep_for(std::chrono::milliseconds(3000));
	MotorControl::Action action1(m,di,1,1.25,true);
	MotorControl::queueAction(action1);
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	return 0;
}
