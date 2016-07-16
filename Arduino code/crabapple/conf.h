#ifndef conf_h
#define conf_h

// include types & constants of Wiring core API
#include <Arduino.h>

#define CMD_BUFFER_SIZE 8

char SERVO_CMD = 'S';
char MOTOR_CMD = 'M';
char LIGHT_CMD = 'L';

char QUERY_CMD = '?';
char DO_CMD = ':';
char SETTIMEOUT_CMD = 't';
char END_OF_CMD = '\n';

const byte num_servos = 4;
const byte num_motors = 2;
const byte num_lights = 1;

//servos (min,max,home,pos values are in degrees)
//pin,min,max,home,pos,timeout(ms)
servo servo0_data = {9,0,180,90,0,5000}; //right wheel
servo servo1_data = {10,0,180,90,0,5000}; //front wheel
servo servo2_data = {11,0,180,90,0,5000}; //back wheel
servo servo3_data = {12,0,180,90,0,5000}; //left wheel

//motors (limit and speed are values between 0-255. direction 0=backwards 1=fowards)
//pwm pin, direction pin1, pin2, speed, limit,direction,timeout(ms)
motor motor0_data = {9,0,180,0,255,1,5000};
motor motor1_data = {10,0,180,0,255,1,5000};

//lights (brightness 0-255)
//pin,default brightness, brightness, timeout(ms)
light light0_data = {9,0,0,5000};

#endif
