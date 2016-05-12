#include <CommonUtil/MotorUtil.hpp>

namespace MotorControl {

std::map<char, double> maxSpeeds;
std::map<char, double> maxCurrents;
std::map<char, long> ctRevs;

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
} // end of namespace MotorControl
