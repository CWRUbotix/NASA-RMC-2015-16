#include <CommonUtil/MotorUtil.hpp>
#include <USBSerial/USBSerial.hpp>
#include <map>
#include <queue>
#include <vector>
#include <thread>

#ifndef MOTORCONTROLSIMPLE_HPP_
#define MOTORCONTROLSIMPLE_HPP_

namespace MotorControl {
extern USBSerial::Port port;
extern volatile bool running;
extern volatile bool stop;

extern std::queue<ActionSimple> actionQueue;
extern std::vector<ActionSimple> actionRunning;
extern volatile bool queue_lock;

int initialize(char* tty);
void runMotorControl();
void execute(ActionSimple);

bool conflictRunning(ActionSimple a);
void removeConflictingRunning(ActionSimple a);
void executeAction(ActionSimple a);

void queueAction(ActionSimple a);
void halt();

}

#endif /* MOTORCONTROLSIMPLE_HPP_ */
