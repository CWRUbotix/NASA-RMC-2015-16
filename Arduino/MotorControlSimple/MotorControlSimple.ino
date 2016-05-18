#include <RoboClaw.h>
#include <BMSerial.h>
#include <SabertoothSimplified.h>

/*
 * pin 2-5 are relays
 * Serial1 tx (18) is saber 
 */


#define MOT_FR          0x00   // Front right motor
#define MOT_FL          0x01   // Front left motor
#define MOT_BR          0x02   // Back right motor
#define MOT_BL          0x03   // Back left motor
#define MOT_TRAL        0x04   // Translating left motor
#define MOT_TRAR        0x05   // Translating right motor
#define MOT_CBUC        0x06   // Conveyor bucket motor
#define MOT_CHOP        0x07   // Conveyor hopper motor
#define ACT_WHEL        0x08   // Left wheel actuator
#define ACT_WHER        0x09   // Right wheel actuator
#define ACT_ARML        0x0A   // Left arm actuator
#define ACT_ARMR        0x0B   // Right arm actuator

#define RCL_WHEELS_L    0x83   // Left wheels RoboClaw address
#define RCL_WHEELS_R    0x80   // Right wheels RoboClaw address
#define RCL_CONVEY      0x82   // Conveyors RoboClaw address
#define RCL_ARM_T       0x81   // Arm translating RoboClaw address

#define LS_WHE_R_B_2    22     // Right back limit switch pos 2
#define LS_WHE_R_B_1    24     // Right back limit switch pos 1
#define LS_WHE_R_F_2    32     // Right front limit switch pos 2
#define LS_WHE_R_F_1    34     // Right front limit switch pos 1
#define LS_ARM_R_1      26     // Right arm rot limit switch pos 1
#define LS_ARM_R_2      28     // Right arm rot limit switch pos 2
#define LS_ARM_R_3      30     // Right arm rot limit switch pos 3

#define LS_WHE_L_B_2    23     // Left back limit switch pos 2
#define LS_WHE_L_B_1    25     // Left back limit switch pos 1
#define LS_WHE_L_F_2    33     // Left front limit switch pos 2
#define LS_WHE_L_F_1    35     // Left front limit switch pos 1
#define LS_ARM_L_1      27     // Right arm rot limit switch pos 1
#define LS_ARM_L_2      29     // Right arm rot limit switch pos 2
#define LS_ARM_L_3      31     // Right arm rot limit switch pos 3

#define CMD_MOT         0x81   // Command for setting motor speeds

#define PIN_STOP        21     // Software stop button

uint8_t leftStates = 0;
uint8_t rightStates = 0;
uint8_t leftStatesLast = 0;
uint8_t rightStatesLast = 0;

uint16_t locksForward = 0;
uint16_t locksBackward = 0;

bool wheelLock = false;        // True if wheels are in the process of changing
bool translateLock = false;    // True if in the process of tilting

volatile bool s_stop = false;  // Software stop

RoboClaw roboclaw(15,14,10000);

void setup() {
  Serial.begin(9600);
  roboclaw.begin(38400);
  pinMode(LS_WHE_R_B_2, INPUT);
  pinMode(LS_WHE_R_B_1, INPUT);
  pinMode(LS_WHE_R_F_2, INPUT);
  pinMode(LS_WHE_R_F_1, INPUT);
  pinMode(LS_ARM_R_1,   INPUT);
  pinMode(LS_ARM_R_2,   INPUT);
  pinMode(LS_ARM_R_3,   INPUT);
  pinMode(LS_WHE_L_B_2, INPUT);
  pinMode(LS_WHE_L_B_1, INPUT);
  pinMode(LS_WHE_L_F_2, INPUT);
  pinMode(LS_WHE_L_F_1, INPUT);
  pinMode(LS_ARM_L_1,   INPUT);
  pinMode(LS_ARM_L_2,   INPUT);
  pinMode(LS_ARM_L_3,   INPUT);
  pinMode(PIN_STOP,     INPUT);

  attachInterrupt(digitalPinToInterrupt(PIN_STOP), softwareStop, CHANGE);
}

void loop() {
  if(s_stop) {
    runMotor(MOT_FR,0);
    runMotor(MOT_FL,0);
    runMotor(MOT_BR,0);
    runMotor(MOT_BL,0);
    runMotor(MOT_TRAL,0);
    runMotor(MOT_TRAR,0);
    runMotor(MOT_CBUC,0);
    runMotor(MOT_CHOP,0);
    runMotor(ACT_WHEL,0);
    runMotor(ACT_WHER,0);
    runMotor(ACT_ARMR,0);
    runMotor(ACT_ARML,0);
  }
  if(Serial.available()) {
    uint8_t head[2];
    Serial.readBytes(head,2);
    uint8_t cmd = head[0];
    uint8_t len = head[1];
    uint8_t packet[len];
    Serial.readBytes(packet,len);
    bool success = true;
    switch(cmd) {
    case CMD_MOT:
      for(int i = 0; i < packet[0]; i++) {
        if(!runMotor(packet[i*2+1],packet[i*2+2])) {
          success = false;
        }
      }
      break;
    }
    
    Serial.write((char)-127);
    Serial.write((char)1);
    if(success) {
      Serial.write((char)1);
    } else {
      Serial.write((char)0);
    }
  }
}

void softwareStop() {
  s_stop = true;
}

void lockForward(uint8_t m) {
  uint16_t mask = 1;
  locksForward |= (mask << m);
}

void lockBackward(uint8_t m) {
  uint16_t mask = 1;
  locksBackward |= (mask << m);
}

void unlockForward(uint8_t m) {
  uint16_t mask = 1;
  locksForward &= ~(mask << m);
}

void unlockBackward(uint8_t m) {
  uint16_t mask = 1;
  locksBackward &= ~(mask << m);
}

bool lockedForward(uint8_t m) {
  uint16_t mask = 1;
  return (bool) ((mask << m) & locksForward);
}

bool lockedBackward(uint8_t m) {
  uint16_t mask = 1;
  return (bool) ((mask << m) & locksBackward);
}

void updateLocks() {
  uint8_t mask = 1;
  if((rightStates & (mask << 7)) && (rightStates & (mask << 5))) {
    lockForward(ACT_WHER);
  } else {
    unlockForward(ACT_WHER);
  }
  if((rightStates & (mask << 6)) && (rightStates & (mask << 4))) {
    lockBackward(ACT_WHER);
  } else {
    unlockBackward(ACT_WHER);
  }
  if((leftStates & (mask << 7)) && (leftStates & (mask << 5))) {
    lockForward(ACT_WHEL);
  } else {
    unlockForward(ACT_WHEL);
  }
  if((leftStates & (mask << 6)) && (leftStates & (mask << 4))) {
    lockBackward(ACT_WHEL);
  } else {
    unlockBackward(ACT_WHEL);
  }
  if((rightStates & (mask << 3)) && (leftStates & (mask << 3))) {
    lockBackward(ACT_ARMR);
  } else {
    unlockBackward(ACT_ARMR);
  }
  if((rightStates & (mask << 1)) && (leftStates & (mask << 1))) {
    lockForward(ACT_ARMR);
  } else {
    unlockForward(ACT_ARMR);
  }

  // TODO Arm actuator limiting
  rightStatesLast = rightStates;
  leftStatesLast = leftStates;
}

void readLimits() {
  if(digitalRead(LS_WHE_R_B_2)) {
    rightStates |= 0b10000000;
  } else {
    rightStates &= 0b01111111;
  }
  if(digitalRead(LS_WHE_R_B_1)) {
    rightStates |= 0b01000000;
  } else {
    rightStates &= 0b10111111;
  }
  if(digitalRead(LS_WHE_R_F_2)) {
    rightStates |= 0b00100000;
  } else {
    rightStates &= 0b11011111;
  }
  if(digitalRead(LS_WHE_R_F_1)) {
    rightStates |= 0b00010000;
  } else {
    rightStates &= 0b11101111;
  }
  if(digitalRead(LS_ARM_R_1)) {
    rightStates |= 0b00001000;
  } else {
    rightStates &= 0b11110111;
  }
  if(digitalRead(LS_ARM_R_2)) {
    rightStates |= 0b00000100;
  } else {
    rightStates &= 0b11111011;
  }
  if(digitalRead(LS_ARM_R_3)) {
    rightStates |= 0b00000010;
  } else {
    rightStates &= 0b11111101;
  }
  
  if(digitalRead(LS_WHE_L_B_2)) {
    leftStates |= 0b10000000;
  } else {
    leftStates &= 0b01111111;
  }
  if(digitalRead(LS_WHE_L_B_1)) {
    leftStates |= 0b01000000;
  } else {
    leftStates &= 0b10111111;
  }
  if(digitalRead(LS_WHE_L_F_2)) {
    leftStates |= 0b00100000;
  } else {
    leftStates &= 0b11011111;
  }
  if(digitalRead(LS_WHE_L_F_1)) {
    leftStates |= 0b00010000;
  } else {
    leftStates &= 0b11101111;
  }
  if(digitalRead(LS_ARM_L_1)) {
    leftStates |= 0b00001000;
  } else {
    leftStates &= 0b11110111;
  }
  if(digitalRead(LS_ARM_L_2)) {
    leftStates |= 0b00000100;
  } else {
    leftStates &= 0b11111011;
  }
  if(digitalRead(LS_ARM_L_3)) {
    leftStates |= 0b00000010;
  } else {
    leftStates &= 0b11111101;
  }
}

int runMotor(uint8_t m, uint8_t s) {
  if(s_stop) {
    s = 0;
  }
  bool dir = (bool) (s & 0b10000000);
  /*
  if(dir && lockedBackward(m)) {
    return 0;
  } else if(~dir && lockedForward(m)) {
    return 0;
  }*/
  s = s & 0b01111111;
  switch(m) {
    case MOT_FR:
      if(dir) {
        roboclaw.BackwardM1(RCL_WHEELS_R,s);
      } else {
        roboclaw.ForwardM1(RCL_WHEELS_R,s);
      }
      break;
    case MOT_FL:
      if(dir) {
        roboclaw.BackwardM1(RCL_WHEELS_L,s);
      } else {
        roboclaw.ForwardM1(RCL_WHEELS_L,s);
      }
      break;
    case MOT_BR:
      if(dir) {
        roboclaw.BackwardM2(RCL_WHEELS_R,s);
      } else {
        roboclaw.ForwardM2(RCL_WHEELS_R,s);
      }
      break;
    case MOT_BL:
      if(dir) {
        roboclaw.BackwardM2(RCL_WHEELS_L,s);
      } else {
        roboclaw.ForwardM2(RCL_WHEELS_L,s);
      }
      break;
    case MOT_TRAL:
      if(dir) {
        roboclaw.BackwardM1(RCL_ARM_T,s);
      } else {
        roboclaw.ForwardM1(RCL_ARM_T,s);
      }
      break;
    case MOT_TRAR:
      if(dir) {
        roboclaw.BackwardM2(RCL_ARM_T,s);
      } else {
        roboclaw.ForwardM2(RCL_ARM_T,s);
      }
      break;
    case MOT_CBUC:
      if(dir) {
        roboclaw.BackwardM1(RCL_CONVEY,s);
      } else {
        roboclaw.ForwardM1(RCL_CONVEY,s);
      }
      break;
    case MOT_CHOP:
      if(dir) {
        roboclaw.BackwardM2(RCL_CONVEY,s);
      } else {
        roboclaw.ForwardM2(RCL_CONVEY,s);
      }
      break;
    case ACT_WHEL:
      if(dir) {
        digitalWrite(2,HIGH);
        digitalWrite(3,LOW);
      } else {
        digitalWrite(3,HIGH);
        digitalWrite(2,LOW);
      }
      break;
    case ACT_WHER:
      if(dir) {
        digitalWrite(4,HIGH);
        digitalWrite(5,LOW);
      } else {
        digitalWrite(5,HIGH);
        digitalWrite(4,LOW);
      }
      break;
    case ACT_ARML:
      break;
    case ACT_ARMR:
      break;
  }
  if(s_stop) {
    return 0;
  }
  return 1;
}

