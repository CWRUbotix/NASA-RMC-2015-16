#ifndef MOTORCONTROL_HPP_
#define MOTORCONTROL_HPP_

#include "MotorControl/MotorUtil.hpp"
#include "USBSerial/USBSerial.hpp"
#include <map>
#include <queue>
#include <vector>
#include <sys/time.h>


namespace MotorControl {
// Serial port to arduino
USBSerial::Port port("");

// Is the motor control thread running
volatile bool running = false;
// Set true to stop the motor control thread
volatile bool stop = false;

// Initialize motor control and spawn the thread
int initialize(char *);

void execute(Action);

void runMotorControl();

std::map<char,Status> stats = std::map<char,Status>();
::timeval last_update, this_update;
std::queue<Action> actionQueue = std::queue<Action>();
std::vector<Action> actionRunning = std::vector<Action>();
volatile bool stats_lock = false;
volatile bool queue_lock = false;
bool conflictRunning(Action);
void removeConflitingRunning(Action);
void updateMotorStatus(char,double,double,double);
long id_counter = 0;

long queueAction(Action);

} // end of namespace MotorControl

#endif // end of MOTORCONTROL_HPP_
