#ifndef conf_h
#define conf_h

// include types & constants of Wiring core API
#include <Arduino.h>

#define CMD_BUFFER_SIZE 8

char SERVO_CMD = 'S';
char MOTOR_CMD = 'M';
char LIGHT_CMD = 'L';
char BUTTON_CMD = 'B';

char QUERY_CMD = '?';
char DO_CMD = ':';
char SETTIMEOUT_CMD = 't';
char END_OF_CMD = '\n';

const byte num_servos = 4;
const byte num_motors = 2;
const byte num_lights = 1;
const byte num_buttons = 2;

//obj arrays need to exist first before config can continue to load
Servo servo_[num_servos];
light lightdata[num_lights];
motor motordata[num_motors];
servo servodata[num_servos];
button buttondata[num_buttons];

void load_conf(){
  //servos (min,max,home,pos values are in degrees)
  //pin,min,max,home,pos,timeout(ms)
  servodata[0] = {9,0,180,90,0,5000}; //right wheel
  servodata[1] = {10,0,180,90,0,5000}; //front wheel
  servodata[2] = {11,0,180,90,0,5000}; //back wheel
  servodata[3] = {12,0,180,90,0,5000}; //left wheel

  //motors (limit and speed are values between 0-255. direction 0=backwards 1=fowards)


  //pwm pin, direction pin1, pin2, speed, limit,direction,timeout(ms)
  motordata[0] = {3,4,2,0,255,1,5000};
  motordata[1] = {5,8,7,0,255,1,5000};

  //lights (brightness 0-255)
  //pin,default brightness, brightness, timeout(ms)
  lightdata[0] = {A1,0,0,5000};

  //buttons
  //pin, state (boolean), timeout
  buttondata[0] = {A2,0,1000};
  buttondata[1] = {A3,0,1000};
}



#endif
