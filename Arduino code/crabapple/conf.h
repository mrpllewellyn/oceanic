#ifndef conf_h
#define conf_h

// include types & constants of Wiring core API
#include <Arduino.h>

const byte CMD_BUFFER_SIZE = 16; // how many commands to hold in a Q.  more commands = more memory used. 

const char SERVO_CMD = 'S';
const char MOTOR_CMD = 'M';
const char LIGHT_CMD = 'L';
const char BUTTON_CMD = 'B';
const char BUZZER_CMD = 'z';
const char PROG_CMD = 'P';

const char QUERY_CMD = '?';
const char DO_CMD = '^';
const char SETTIMEOUT_CMD = 't';
const char SETRATE_CMD = 'r';
const char RESET_CMD = 'x';
const char END_OF_CMD = '\n';

const byte num_servos = 4;
const byte num_motors = 2;
const byte num_lights = 1;
const byte num_buttons = 2;
const byte num_buzzers = 1;
const byte num_programs = 5;

//obj arrays need to exist first before config can continue to load
Servo servo_[num_servos];
light light_obj[num_lights];
motor motor_obj[num_motors];
servo servo_obj[num_servos];
button button_obj[num_buttons];
buzzer buzzer_obj[num_buzzers];
prgm prgm_obj[num_programs];
void (*programPtrs[num_programs])(int index);

void load_conf() { // here we put the information about our different objects. not all of the object properties are exposed here, only the ones we may want to set at compile time.
                    //this was done by putting the user important ones at the beginning of the struct and the runtime ones at the end.
                    //those can be passed here too by declaring the rest of the struct, but they are things that dont need to be preconfigured so can remain null
                    
  //servos (min, max, home are in degrees). home is the default position of the servo. min and max are the bounds
  //pin,min,max,home,pos,timeout(s), description
  servo_obj[0] = {9, 0, 180, 90, 5, F("R Wheel")}; 
  servo_obj[1] = {10, 0, 180, 90, 5, F("F Wheel")}; 
  servo_obj[2] = {11, 0, 180, 90, 5, F("B Wheel")}; 
  servo_obj[3] = {12, 0, 180, 90, 5, F("L Wheel")};
  
  //motors (limitis a value between 0-255)
  //pwm pin, direction pin1, pin2, min speed, max speed,timeout(s), description
  motor_obj[0] = {3, 4, 2, 60, 255, 5, F("R Motor")};
  motor_obj[1] = {5, 8, 7, 60, 255, 5, F("L Motor")};

  //lights (brightness 0-255)
  //pin, default brightness, timeout(s), description
  light_obj[0] = {A1, 0, 5, F("Blue LED")};

  //buttons
  //pin, timeout(s), description
  button_obj[0] = {A2, F("R bumper")};
  button_obj[1] = {A3, F("L bumper")};

  //buzzers
  //pin
  buzzer_obj[0] = {(A0)};

  //programs
  //timeout(s), description
  prgm_obj[0] = {5, F("forward")};
  prgm_obj[1] = {5, F("reverse")};
  prgm_obj[2] = {5, F("turn L")};
  prgm_obj[3] = {5, F("turn R")};
  prgm_obj[4] = {5, F("test")};

}

#endif
