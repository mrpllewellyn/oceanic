#ifndef conf_h
#define conf_h

// include types & constants of Wiring core API
#include <Arduino.h>

#define CMD_BUFFER_SIZE 8

char SERVO_CMD = 'S';
char MOTOR_CMD = 'M';
char LIGHT_CMD = 'L';
char BUTTON_CMD = 'B';
char PROG_CMD = 'P';

char QUERY_CMD = '?';
char DO_CMD = ':';
char SETTIMEOUT_CMD = 't';
char END_OF_CMD = '\n';

const byte num_servos = 4;
const byte num_motors = 2;
const byte num_lights = 1;
const byte num_buttons = 2;
const byte num_programs = 5;

//obj arrays need to exist first before config can continue to load
Servo servo_[num_servos];
light lightdata[num_lights];
motor motordata[num_motors];
servo servodata[num_servos];
button buttondata[num_buttons];
prog progdata[num_programs];
void (*programPtrs[num_programs])(int index);

void load_conf() {
  //servos (min,max,home,pos values are in degrees)
  //pin,min,max,home,pos,timeout(ms), desc
  servodata[0] = {9, 0, 180, 90, 0, 5000, F("R Wheel")}; 
  servodata[1] = {10, 0, 180, 90, 0, 5000, F("F Wheel")}; 
  servodata[2] = {11, 0, 180, 90, 0, 5000, F("B Wheel")}; 
  servodata[3] = {12, 0, 180, 90, 0, 5000, F("L Wheel")};
  
  //motors (limit and speed are values between 0-255. direction 0=backwards 1=fowards)
  //pwm pin, direction pin1, pin2, speed, limit,direction,timeout(ms), desc
  motordata[0] = {3, 4, 2, 0, 255, 1, 5000, F("R Motor")};
  motordata[1] = {5, 8, 7, 0, 255, 1, 5000, F("L Motor")};

  //lights (brightness 0-255)
  //pin,default brightness, brightness, timeout(ms), desc
  lightdata[0] = {A1, 0, 0, 5000, F("Blue LED")};

  //buttons
  //pin, state (boolean), timeout, desc
  buttondata[0] = {A2, 0, 50, F("R bumper")};
  buttondata[1] = {A3, 0, 50, F("L bumper")};

  //programs
  //state, timeout, desc
  progdata[0] = {0, 5000, F("forward")};
  progdata[1] = {0, 5000, F("reverse")};
  progdata[2] = {0, 5000, F("turn L")};
  progdata[3] = {0, 5000, F("turn R")};
  progdata[4] = {0, 5000, F("test")};

}

#endif
