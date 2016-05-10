#include "MotorControl/MotorControl.hpp"
#include "MotorControl/MotorUtil.hpp"
#include "I2C/I2C.hpp"
#include <stdio.h>
#include <memory>
#include <thread>

namespace MotorControl {

// Initialize the motor control thread to a usb arduino device
int initialize(char * device) {
	initializeMaximums();
	USBSerial::Port port(device);
	if(port.open() < 0) {
		::perror("Failed to start Motor Control");
		return -1;
	}
	// Launch the thread
	std::thread t1(runMotorControl);
	running = true;
	return 0;
}

// The main motor control thread
void runMotorControl() {
	while(!stop) {
		// Update motor status
		// Write the status command
		port.write(SCMD_ST);
		char tmp[2];
		// Read response header
		port.read(tmp,2);
		char buff[tmp[1]];
		// Read response body
		port.read(buff,tmp[1]);
		// Calc change in time
		::gettimeofday(&this_update,NULL);
		double dt = ((double)(this_update.tv_usec-last_update.tv_sec))/1000000;
		// Update speeds and currents
		int cps;
		short cu;
		for(int i = 0; i < tmp[1]/3; i++) {
			::memcpy(&cps,buff+i*7+1,4);
			::memcpy(&cu,buff+i*7+5,2);
			double speed = convertVelocity(buff[i*7],cps);
			double current = 0.01*(double)cu;
			updateMotorStatus(buff[i*3],speed,current,dt);
		}
		// Update actions
		Action a;
		for(int j = 0; j < (int)actionRunning.size(); j++) {
			a = actionRunning.at(j);
			// Calc average velocity
			double vel_avg;
			for(int i = 0; i < a.num_motors; i++) {
				if(a.direction[i]) {
					vel_avg += stats.find(a.motor[i])->second.speed_inst;
				} else {
					vel_avg -= stats.find(a.motor[i])->second.speed_inst;
				}
			}
			vel_avg /= a.num_motors;
			a.speed_rt = vel_avg;
			// If not measuring distance, skip
			if(!a.use_dist) {
				continue;
			}
			// Calc distance left
			a.distance_remaining -= vel_avg*dt;
			// If finished, set to done and erase
			if(a.distance_remaining < 0) {
				// Mark as done
				a.status = STAT_ACTION_DONE;
				// Create stop action
				Action stop;
				::memcpy(&stop,&a,sizeof(Action));
				stop.speed = 0;
				stop.use_dist = false;
				stop.ovr = true;
				queueAction(stop);
				// Erase
				actionRunning.erase(actionRunning.begin()+j);
			}
		}
		// Set last time
		::memcpy(&last_update,&this_update,sizeof(::timeval));
		// Run the queue
		// Wait for queue to be unlocked
		while(queue_lock) {}
		queue_lock = true;
		// Run queue of actions
		while(!actionQueue.empty()) {
			Action tmp = actionQueue.front();
			// If it does not override and conflicts with running actions, skip
			if(!tmp.ovr && conflictRunning(tmp)) {
				tmp.status = STAT_ACTION_NORUN;
				actionQueue.pop();
				continue;
			}
			// Stage for running and execute
			tmp.status = STAT_ACTION_TORUN;
			removeConflitingRunning(tmp);
			execute(tmp);
			actionRunning.push_back(tmp);
		}
		queue_lock = false;
	}
	running = false;
}

// Execute an action (only run by the main motor control thread
void execute(Action action) {
	int len = action.num_motors*2+2;
	char packet[len];
	packet[0] = SCMD_MOT;
	packet[1] = action.num_motors*2;
	for(int i = 0; i < action.num_motors; i++) {
		packet[2+i*2] = action.motor[i];
		packet[3+i*2] = scaleVelocity(action.motor[i],action.speed);
		if(!action.direction[i]) {
			packet[3+i*2] *= -1;
		}
	}
	port.write(packet,len);
	char resp[3];
	port.read(resp,3);
	if(resp[2] == 0x00) {
		action.status = STAT_ACTION_RUN;
	} else {
		action.status = STAT_ACTION_FAIL;
	}

}

// Add an action to the queue
long queueAction(Action action) {
	// Timeout for a lock on queue
	::timeval i,e;
	::gettimeofday(&i,NULL);
	while(queue_lock) {
		::gettimeofday(&e,NULL);
		// 100 ms timeout
		if((e.tv_usec-i.tv_usec) > 100000) {
			return 0;
		}
	};
	// Add an action to the queue
	queue_lock = true;
	actionQueue.push(action);
	queue_lock = false;
	// Set id to id_counter
	action.id = id_counter;
	id_counter++;
	return id_counter;
}

// Update the status of a motor (only called by main motor thread
void updateMotorStatus(char m, double s, double c, double dt) {
	Status tmp = stats.find(m)->second;
	tmp.speed_avg += (s+tmp.speed_inst)*dt/2;
	tmp.power_avg += (c*13.4+tmp.power_inst)*dt/2;
}

// Checks if an action conflicts with other actions that are running
bool conflictRunning(Action action) {
	for(int i = 0; i < (int)actionRunning.size(); i++) {
		for(int j = 0; j < action.num_motors; j++) {
			for(int k = 0; k < actionRunning.at(i).num_motors; k++) {
				if(action.motor[j] == actionRunning.at(i).motor[k]) {
					return true;
				}
			}
		}
	}
	return false;
}

// Removes all actions that conflict with a given action
void removeConflictingRunning(Action action) {
	for(int i = 0; i < (int)actionRunning.size(); i++) {
		for(int j = 0; j < action.num_motors; j++) {
			for(int k = 0; k < actionRunning.at(i).num_motors; k++) {
				if(action.motor[j] == actionRunning.at(i).motor[k]) {
					actionRunning.erase(actionRunning.begin()+i);
				}
			}
		}
	}
}

}
