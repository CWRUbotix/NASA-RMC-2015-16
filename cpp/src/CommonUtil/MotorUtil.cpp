#include <CommonUtil/MotorUtil.hpp>

namespace MotorControl {

std::map<char, double> maxSpeeds;
std::map<char, double> maxCurrents;
std::map<char, int> ctRevs;

char scaleVelocity(char motor, double val) {
	return scaleChar(val, maxSpeeds.find(motor)->second,127);
}

char scaleCurrent(char motor, double val) {
	return scaleChar(val, maxCurrents.find(motor)->second,255);
}

double unscaleVelocity(char motor, char val) {
	return ((double)val)*(maxSpeeds.find(motor)->second)/127;
}

double unscaleCurrent(char motor, char val) {
	return ((double)val)*(maxCurrents.find(motor)->second)/255;
}

char scaleChar(double val, double max, char max_c) {
	double scaled = max_c*val/max;
	if(scaled > max_c) {
		scaled = max_c;
	} else if(scaled < 0) {
		scaled = 0;
	}
	return (char)scaled;
}

double convertVelocity(char motor, int val) {
	return 1;
}

void initializeMaximums() {
	maxSpeeds.insert(std::pair<char,double>(MOT_FR,2.5));
	maxSpeeds.insert(std::pair<char,double>(MOT_BR,2.5));
	maxSpeeds.insert(std::pair<char,double>(MOT_FL,2.5));
	maxSpeeds.insert(std::pair<char,double>(MOT_BL,2.5));
	maxSpeeds.insert(std::pair<char,double>(MOT_TRAL,2.5));
	maxSpeeds.insert(std::pair<char,double>(MOT_TRAR,2.5));
	maxSpeeds.insert(std::pair<char,double>(MOT_CBUC,2.5));
	maxSpeeds.insert(std::pair<char,double>(MOT_CHOP,2.5));
	maxSpeeds.insert(std::pair<char,double>(ACT_WHEL,2.5));
	maxSpeeds.insert(std::pair<char,double>(ACT_WHER,2.5));
	maxSpeeds.insert(std::pair<char,double>(ACT_ARML,2.5));
	maxSpeeds.insert(std::pair<char,double>(ACT_ARMR,2.5));

	maxCurrents.insert(std::pair<char,double>(MOT_FR,2.5));
	maxCurrents.insert(std::pair<char,double>(MOT_BR,2.5));
	maxCurrents.insert(std::pair<char,double>(MOT_FL,2.5));
	maxCurrents.insert(std::pair<char,double>(MOT_BL,2.5));
	maxCurrents.insert(std::pair<char,double>(MOT_TRAL,2.5));
	maxCurrents.insert(std::pair<char,double>(MOT_TRAR,2.5));
	maxCurrents.insert(std::pair<char,double>(MOT_CBUC,2.5));
	maxCurrents.insert(std::pair<char,double>(MOT_CHOP,2.5));
	maxCurrents.insert(std::pair<char,double>(ACT_WHEL,2.5));
	maxCurrents.insert(std::pair<char,double>(ACT_WHER,2.5));
	maxCurrents.insert(std::pair<char,double>(ACT_ARML,2.5));
	maxCurrents.insert(std::pair<char,double>(ACT_ARMR,2.5));
}

std::string ActionSimple::toString() {
	int len_t = 0;
	char out[20*this->num_motors];
	for(int i = 0; i < this->num_motors; i++) {
		int len = 0;
		if(this->direction[i]) {
			len = sprintf(out+len_t,"M:%d S:%d D:1\n",this->motor[i],this->speed);
		} else {
			len = sprintf(out+len_t,"M:%d S:%d D:0\n",this->motor[i],this->speed);
		}
		len_t += len;
	}
	return std::string(out);
}

Action::Action(char* m,bool* dr,char n,double s,double d,bool o,bool ds) {
	motor = m;
	direction = dr;
	speed = s;
	speed_rt = s;
	distance = d;
	distance_remaining = d;
	ovr = o;
	use_dist = ds;
	num_motors = n;
	len_serialized = n*2 + 11;
	serialized = (char*) ::malloc(len_serialized);
	serialized[0] = n;
	::memcpy(serialized+1,&s,4);
	::memcpy(serialized+5,&d,4);
	serialized[9] = (char) o;
	serialized[10] = (char) ds;
	::memcpy(serialized+11,m,n);
	::memcpy(serialized+11+n,(char*)dr,n);
	status = STAT_ACTION_DONE;
	id = 0;
}

Action::Action(char* m,bool* dr,char n,double s,bool o) : Action(m,dr,n,s,0,o,false) {}

Action::Action(char * s, int n) {
	num_motors = s[0];
	::memcpy(&speed,s+1,4);
	speed_rt = speed;
	::memcpy(&distance,s+5,4);
	distance_remaining = distance;
	ovr = (bool)s[9];
	use_dist = (bool)s[10];
	motor = (char*) malloc(num_motors);
	::memcpy(s+11,motor,num_motors);
	direction = (bool*) malloc(num_motors);
	::memcpy(s+11+num_motors,direction,num_motors);
	serialized = s;
	len_serialized = n;
	status = STAT_ACTION_DONE;
	id = 0;
}

Action::Action() : Action(NULL,NULL,0,0,0,false,false) {}
Action::~Action() {}

ActionSimple::ActionSimple(uint8_t* m, bool* dr, uint8_t n, uint8_t sp) {
	motor = (uint8_t*)::malloc(n);
	direction = (bool*)::malloc(n);
	::memcpy(motor,m,n);
	::memcpy(direction,dr,n);
	speed = sp;
	num_motors = n;
	len_serialized = n*2+1;
	serialized = (uint8_t*)::malloc(len_serialized);
	serialized[0] = num_motors;
	for(int i = 0; i < num_motors; i++) {
		serialized[i*2+1] = motor[i];
		if(!direction[i]) {
			serialized[i*2+2] = speed | 0b10000000;
		} else {
			serialized[i*2+2] = speed;
		}
	}
}

ActionSimple::ActionSimple(uint8_t* s, int n) {
	serialized = (uint8_t*)::malloc(n);
	::memcpy(serialized,s,n);
	len_serialized = n;
	num_motors = s[0];
	motor = (uint8_t*)::malloc(num_motors);
	direction = (bool*)::malloc(num_motors);
	for(int i = 0; i < num_motors; i++) {
		motor[i] = serialized[i*2+1];
		if(serialized[i*2+2] & 0b10000000) {
			direction[i] = true;
		} else {
			direction[i] = false;
		}
	}
	speed = serialized[2] & 0b01111111;
}

ActionSimple::ActionSimple() {
	motor = nullptr;
	direction = nullptr;
	speed = 0;
	num_motors = 0;
	serialized = nullptr;
	len_serialized = 0;
}

ActionSimple::~ActionSimple() {}

Action forward(double speed, bool ovr) {
	char m[4] = {MOT_FR,MOT_FL,MOT_BR,MOT_BL};
	bool d[4] = {true,true,true,true};
	Action a(m,d,4,speed,0,ovr,false);
	return a;
}
Action forward(double speed, double dist, bool ovr) {
	char m[4] = {MOT_FR,MOT_FL,MOT_BR,MOT_BL};
	bool d[4] = {true,true,true,true};
	Action a(m,d,4,speed,dist,ovr,true);
	return a;
}
Action backward(double speed, bool ovr) {
	char m[4] = {MOT_FR,MOT_FL,MOT_BR,MOT_BL};
	bool d[4] = {false,false,false,false};
	Action a(m,d,4,speed,0,ovr,false);
	return a;
}
Action backward(double speed, double dist, bool ovr) {
	char m[4] = {MOT_FR,MOT_FL,MOT_BR,MOT_BL};
	bool d[4] = {false,false,false,false};
	Action a(m,d,4,speed,dist,ovr,true);
	return a;
}
Action turnLeft(double speed, bool ovr) {
	char m[4] = {MOT_FR,MOT_FL,MOT_BR,MOT_BL};
	bool d[4] = {true,false,true,false};
	Action a(m,d,4,speed,0,ovr,false);
	return a;
}
Action turnLeft(double speed, double angle, bool ovr) {
	char m[4] = {MOT_FR,MOT_FL,MOT_BR,MOT_BL};
	bool d[4] = {true,false,true,false};
	Action a(m,d,4,speed,angle,ovr,true);
	return a;
}
Action turnRight(double speed, bool ovr) {
	char m[4] = {MOT_FR,MOT_FL,MOT_BR,MOT_BL};
	bool d[4] = {false,true,false,true};
	Action a(m,d,4,speed,0,ovr,false);
	return a;
}
Action turnRight(double speed, double angle, bool ovr) {
	char m[4] = {MOT_FR,MOT_FL,MOT_BR,MOT_BL};
	bool d[4] = {false,true,false,true};
	Action a(m,d,4,speed,angle,ovr,true);
	return a;
}
Action openWheels(bool ovr) {
	char m[2] = {ACT_WHEL,ACT_WHER};
	bool d[2] = {true,true};
	Action a(m,d,2,1,0,ovr,false);
	return a;
}
Action closeWheels(bool ovr) {
	char m[2] = {ACT_WHEL,ACT_WHER};
	bool d[2] = {false,false};
	Action a(m,d,2,1,0,ovr,false);
	return a;
}
Action tiltArmDown(double speed, double angle) {
	char m[2] = {ACT_ARML,ACT_ARMR};
	bool d[2] = {true,true};
	Action a(m,d,2,speed,angle,true,true);
	return a;
}
Action tiltArmUp(double speed, double angle) {
	char m[2] = {ACT_ARML,ACT_ARMR};
	bool d[2] = {false,false};
	Action a(m,d,2,speed,angle,true,true);
	return a;
}
Action translateArmDown(double speed, double distance) {
	char m[2] = {MOT_TRAL,MOT_TRAR};
	bool d[2] = {true,true};
	Action a(m,d,2,speed,distance,true,true);
	return a;
}
Action translateArmDown(double speed) {
	char m[2] = {MOT_TRAL,MOT_TRAR};
	bool d[2] = {true,true};
	Action a(m,d,2,speed,0,true,true);
	return a;
}
Action translateArmUp(double speed, double distance) {
	char m[2] = {MOT_TRAL,MOT_TRAR};
	bool d[2] = {false,false};
	Action a(m,d,2,speed,distance,true,true);
	return a;
}
Action translateArmUp(double speed) {
	char m[2] = {MOT_TRAL,MOT_TRAR};
	bool d[2] = {false,false};
	Action a(m,d,2,speed,0,true,true);
	return a;
}
Action bucketForward(double speed) {
	char m[1] = {MOT_CBUC};
	bool d[1] = {true};
	Action a(m,d,1,speed,0,true,true);
	return a;
}
Action bucketBackward(double speed) {
	char m[1] = {MOT_CBUC};
	bool d[1] = {false};
	Action a(m,d,1,speed,0,true,true);
	return a;
}
Action hopperOut(double speed) {
	char m[1] = {MOT_CHOP};
	bool d[1] = {true};
	Action a(m,d,1,speed,0,true,true);
	return a;
}
Action hopperOut(double speed, double dist) {
	char m[1] = {MOT_CHOP};
	bool d[1] = {true};
	Action a(m,d,1,speed,dist,true,true);
	return a;
}
Action hopperIn(double speed) {
	char m[1] = {MOT_CHOP};
	bool d[1] = {false};
	Action a(m,d,1,speed,0,true,true);
	return a;
}
Action hopperIn(double speed, double dist) {
	char m[1] = {MOT_CHOP};
	bool d[1] = {false};
	Action a(m,d,1,speed,dist,true,true);
	return a;
}

Action stopAll() {
	char m[12] = {MOT_FR,MOT_FL,MOT_BR,MOT_BL,MOT_TRAL,MOT_TRAR,MOT_CBUC,MOT_CHOP,ACT_WHEL,ACT_WHER,ACT_ARML,ACT_ARMR};
	bool d[12];
	Action a(m,d,12,0,0,true,false);
	return a;
}

} // end of namespace MotorControl
