#ifndef conf_h
#define conf_h

// include types & constants of Wiring core API
#include <Arduino.h>

#define CMD_BUFFER_SIZE 8 // how many commands to hold in a Q.  more commands = more memory used. 

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

void load_conf() { // here we put the information about our different objects. not all of the object properties are exposed here, only the ones we may want to set at compile time.
                    //this was done by putting the user important ones at the beginning of the struct and the runtime ones at the end.
                    //those can be passed here too by declaring the rest of the struct, but they are things that dont need to be preconfigured so can remain null
                    
  //servos (min, max, home are in degrees). home is the default position of the servo. min and max are the bounds
  //pin,min,max,home,pos,timeout(ms), desc
  servodata[0] = {9, 0, 180, 90, 5, F("R Wheel")}; 
  servodata[1] = {10, 0, 180, 90, 5, F("F Wheel")}; 
  servodata[2] = {11, 0, 180, 90, 5, F("B Wheel")}; 
  servodata[3] = {12, 0, 180, 90, 5, F("L Wheel")};
  
  //motors (limitis a value between 0-255)
  //pwm pin, direction pin1, pin2, speed_limit,timeout(ms), desc
  motordata[0] = {3, 4, 2, 255, 5, F("R Motor")};
  motordata[1] = {5, 8, 7, 255, 5, F("L Motor")};

  //lights (brightness 0-255)
  //pin, default brightness, timeout(ms), desc
  lightdata[0] = {A1, 0, 5, F("Blue LED")};

  //buttons
  //pin, timeout, desc
  buttondata[0] = {A2, 0.5, F("R bumper")};
  buttondata[1] = {A3, 0.5, F("L bumper")};

  //programs
  //timeout, desc
  progdata[0] = {5, F("forward")};
  progdata[1] = {5, F("reverse")};
  progdata[2] = {5, F("turn L")};
  progdata[3] = {5, F("turn R")};
  progdata[4] = {5, F("test")};

}

#endif
