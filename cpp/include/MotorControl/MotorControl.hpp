#ifndef MOTORCONTROL_HPP_
#define MOTORCONTROL_HPP_

#include <CommonUtil/MotorUtil.hpp>
#include <USBSerial/USBSerial.hpp>
#include <map>
#include <queue>
#include <vector>
#include <sys/time.h>
#include <thread>


namespace MotorControl {
// Serial port to arduino
extern USBSerial::Port port;

// Is the motor control thread running
extern volatile bool running;
// Set true to stop the motor control thread
extern volatile bool stop;

// Initialize motor control and spawn the thread
int initialize(char *);

void execute(Action);

void runMotorControl();

extern std::map<char,Status> stats;
extern ::timeval last_update, this_update;
extern std::queue<Action> actionQueue;
extern std::vector<Action> actionRunning;
extern volatile bool stats_lock;
extern volatile bool queue_lock;
bool conflictRunning(Action);
void removeConflictingRunning(Action);
void updateMotorStatus(char,double,double,double);
extern long id_counter;
extern std::thread t1;

long queueAction(Action);

int halt();

} // end of namespace MotorControl

#endif // end of MOTORCONTROL_HPP_
