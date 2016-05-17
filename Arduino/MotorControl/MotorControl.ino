#include "RoboClaw.h"
#include "BMSerial.h"
#include <SabertoothSimplified.h>

#define SERIAL_READ 0x00
#define MOTOR_READ 0x01
#define EXECUTE 0x02

#define ADDRESS		0x01

// Addresses for roboclaws
#define	WHEELS_L	0x83	// Left wheels
#define	WHEELS_R	0x80	// Right wheels
#define	CONVEY		0x82	// Conveyors (M1 is arm, M2 is hopper)
#define	ARM_T		0x81	// Arm translation

// Pins for limit switches
#define	ARM_L_L_O	38		// Arm actuator left open
#define	ARM_L_L_C	39		// Arm actuator left close
#define	ARM_L_R_O	40		// Arm actuator right open
#define	ARM_L_R_C	41		// Arm actuator right close
#define	WHE_L_L_O	42		// Wheel actuator left open
#define	WHE_L_L_C	43		// Wheel actuator left close
#define	WHE_L_R_O	44		// Wheel actuator right open
#define	WHE_L_R_C	45		// Wheel actuator right close

// Serial commands
#define CMD_WHO		0x80	// Who is
#define CMD_MOT		0x81	// Control motors
#define CMD_ST		0x82	// Get status

// Motor id's
#define MOT_FR		0x00	// Front right motor
#define MOT_FL		0x01	// Front left motor
#define MOT_BR		0x02	// Back right motor
#define MOT_BL		0x03	// Back left motor
#define MOT_TRAL	0x04	// Translating left motor
#define MOT_TRAR	0x05	// Translating right motor
#define MOT_CBUC	0x06	// Conveyor bucket motor
#define MOT_CHOP	0x07	// Conveyor hopper motor
#define ACT_WHEL	0x08	// Left wheel actuator
#define ACT_WHER	0x09	// Right wheel actuator
#define ACT_ARML	0x0A	// Left arm actuator
#define ACT_ARMR	0x0B	// Right arm actuator

#define	PIN_STOP	21		// Stop all motors

volatile bool stp = false;

bool wheels_open = false;
bool wheel_lock = false;
bool tilt_lock = false;

char state = SERIAL_READ;

char motor_vel[12];
long read_motor_vel[12];
char motor_vel_next[12];
int read_motor_current[12];

RoboClaw roboclaw(15, 14, 10000);
BMSerial st(17,16);
//SabertoothSimplified ST;
void setup() {
  digitalWrite(13,HIGH);
	Serial.begin(9600);
	roboclaw.begin(38400);
	pinMode(ARM_L_L_O, INPUT);
	pinMode(ARM_L_L_C, INPUT);
	pinMode(ARM_L_R_O, INPUT);
	pinMode(ARM_L_R_C, INPUT);
	pinMode(WHE_L_L_O, INPUT);
	pinMode(WHE_L_L_C, INPUT);
	pinMode(WHE_L_R_O, INPUT);
	pinMode(WHE_L_R_C, INPUT);
	pinMode(PIN_STOP, INPUT);
	attachInterrupt(digitalPinToInterrupt(PIN_STOP), stopInterrupt, CHANGE);
}

void loop() {
	switch(state) {
	case SERIAL_READ:
		if(Serial.available() > 0) {
      char in[2];
      Serial.readBytes(in,2);
			char pkg[in[1]];
			Serial.readBytes(pkg, in[1]);
			parse_command(in[0], pkg, in[1]);
		}
		state = MOTOR_READ;
		break;
	case MOTOR_READ:
		//readMotors();
		//readCurrents();
		//readLimits();
		state = EXECUTE;
		break;
	case EXECUTE:
		for(int i = 0; i < 12; i++) {
			if(motor_vel_next[i] != motor_vel[i]) {
				//runMotor(i,motor_vel_next[i]);
			}
		}
    memcpy(&motor_vel_next,&motor_vel,12);
		state = SERIAL_READ;
		break;
	}

}

void parse_command(char cmd, char * packet, char len) {
	switch(cmd) {
	case (char)CMD_WHO:
 Serial.write(CMD_WHO);
    Serial.write((char)1);
    Serial.write(ADDRESS);
		break;
	case (char)CMD_MOT:
		memcpy(&motor_vel, &motor_vel_next, 12);
		for(int i = 0; i < len/2; i++) {
      runMotor(packet[i*2],packet[i*2+1]);
			motor_vel_next[packet[i*2]] = packet[i*2+1];
		}
		char out[3];
		out[0] = CMD_MOT;
		out[1] = 1;
		if(stp) {
			out[2] = 1;
		} else {
			out[2] = 0;
		}
		Serial.write(out,3);
		break;
	case (char)CMD_ST:
		char out2[7*12+2];
    out2[0] = CMD_ST;
    out2[1] = (char)(7*12);
		for(int i = 0; i < 12; i++) {
			out2[i*7] = i;
			memcpy(out2+i*7+3,&read_motor_vel[i],4);
			memcpy(out2+i*7+7,&read_motor_current[i],2);
		}
		Serial.write(out2,7*12+2);
		break;
	}
}

void stopInterrupt() {
	if(digitalRead(PIN_STOP)) {
		for(int i = 0; i < 12; i++) {
			runMotor(i, 0);
		}
		stp = true;
	} else {
		stp = false;
	}
}

void readMotors() {
	read_motor_vel[0] = roboclaw.ReadSpeedM1(WHEELS_R);
	read_motor_vel[1] = roboclaw.ReadSpeedM1(WHEELS_L);
	read_motor_vel[2] = roboclaw.ReadSpeedM2(WHEELS_R);
	read_motor_vel[3] = roboclaw.ReadSpeedM2(WHEELS_L);
	read_motor_vel[4] = roboclaw.ReadSpeedM1(ARM_T);
	read_motor_vel[5] = roboclaw.ReadSpeedM2(ARM_T);
	read_motor_vel[6] = roboclaw.ReadSpeedM1(CONVEY);
	read_motor_vel[7] = roboclaw.ReadSpeedM2(CONVEY);
}

void readCurrents() {

}

void readLimits() {
	if(digitalRead(ARM_L_L_O)) {
		motor_vel_next[ACT_ARML] = 0;
	}
	if(digitalRead(ARM_L_L_C)) {
		motor_vel_next[ACT_ARML] = 0;
	}
	if(digitalRead(ARM_L_R_O)) {
		motor_vel_next[ACT_ARMR] = 0;
	}
	if(digitalRead(ARM_L_R_C)) {
		motor_vel_next[ACT_ARMR] = 0;
	}
	if(digitalRead(WHE_L_L_O)) {
		motor_vel_next[ACT_WHEL] = 0;
	}
	if(digitalRead(WHE_L_L_C)) {
		motor_vel_next[ACT_WHEL] = 0;
	}
	if(digitalRead(WHE_L_R_O)) {
		motor_vel_next[ACT_WHER] = 0;
	}
	if(digitalRead(WHE_L_R_C)) {
		motor_vel_next[ACT_WHER] = 0;
	}
}

void runMotor(char m, char sp) {
	switch(m) {
	case MOT_FR:
		roboclaw.SpeedM1(WHEELS_R,sp);
		break;
	case MOT_FL:
		roboclaw.SpeedM1(WHEELS_L,sp);
		break;
	case MOT_BR:
		roboclaw.SpeedM2(WHEELS_R,sp);
		break;
	case MOT_BL:
		roboclaw.SpeedM2(WHEELS_L,sp);
		break;
	case MOT_TRAL:
		roboclaw.SpeedM1(ARM_T,sp);
		break;
	case MOT_TRAR:
		roboclaw.SpeedM2(ARM_T,sp);
		break;
	case MOT_CBUC:
		roboclaw.SpeedM1(CONVEY,sp);
		break;
	case MOT_CHOP:
		roboclaw.SpeedM2(CONVEY,sp);
		break;
	case ACT_WHEL:
		//st1.motor(1,sp);
		break;
	case ACT_WHER:
		//st1.motor(2,sp);
		break;
	case ACT_ARML:
		//st1.motor(2,sp);
		break;
	case ACT_ARMR:
		//st2.motor(1,sp);
		break;
	}
	motor_vel[m] = sp;
}

