#include <MotorControl/MotorControlSimple.hpp>

namespace MotorControl {
USBSerial::Port port("");
volatile bool running;
volatile bool stop;

std::queue<ActionSimple> actionQueue;
std::vector<ActionSimple> actionRunning;
volatile bool queue_lock;

int initialize(char* tty) {
	port.device = std::string(tty);
	printf("Opening communication with motor controller\n");
	if(port.open() < 0) {
		printf("Failed to launch motor controller\n");
		//return -1;
	}
	printf("Successful connection\n");
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	printf("Launching motor controller hog\n");
	std::thread t1(runMotorControl);
	t1.detach();
	running = true;
	return 0;
}

void runMotorControl() {
	printf("Motor control thread running\n");
	while(!stop) {
		while(queue_lock) {}
		queue_lock = true;
		while(!actionQueue.empty()) {
			printf("Dequeuing action\n");
			printf("%s",actionQueue.front().toString().c_str());
			executeAction(actionQueue.front());
			actionQueue.pop();
			printf("Dequeued\n");
		}
		queue_lock = false;
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}
	printf("Motor control thread exiting\n");
}

void queueAction(ActionSimple a) {
	while(queue_lock){}
	queue_lock = true;
	actionQueue.push(a);
	queue_lock = false;
}

void executeAction(ActionSimple a) {
	printf("Executing action\n");
	char packet[a.len_serialized + 2];
	packet[0] = SCMD_MOT;
	packet[1] = a.len_serialized;
	::memcpy(packet+2,a.serialized,a.len_serialized);
	char buff[3];
	while((buff[0] != (char)SCMD_MOT)){
		port.write(packet,a.len_serialized+2);
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		port.read(buff,3);
	}
	printf("Done executing\n");
}

void halt() {
	stop = true;
}

}

