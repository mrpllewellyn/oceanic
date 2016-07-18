#ifndef structs_h
#define structs_h

// include types & constants of Wiring core API
#include <Arduino.h>

struct servo { // struct for servo object type
  byte Pin;      // the number of the servo pin
  byte Min;     //servo min allowed position
  byte Max;     //servo max allowed position
  byte Home;    //servo default position
  byte Pos;     //servo position
  unsigned int Timeout; //timeout
  byte rate; //the speed the servo moves min0-255max
  String Desc; //object description
  unsigned long lastMillis; //record of when unit was last run
};

struct motor {
  byte speedPin;      // the number of the pwm pin
  byte dirPin1;
  byte dirPin2;
  byte Speed;
  byte Limit;
  boolean Direction;
  unsigned int Timeout;
  byte rate; //the (de)accell of the motor min 0 max 255
  String Desc;
  unsigned long lastMillis;
};

struct light {
  byte Pin;      // the number of the light pin
  byte default_brightness;
  byte brightness;
  unsigned int Timeout;
  byte rate; //how quickly the light updates min 0 max 255
  String Desc;
  unsigned long lastMillis;
};

struct button {
  byte Pin;
  boolean state;
  unsigned int Timeout;
  String Desc;
  unsigned long lastMillis;
};

struct cmd {
  char obj_type;
  byte obj_number;
  char action_type;
  int value;
};

struct prog {
  boolean state;
  unsigned int Timeout;
  byte rate; //how quickly the program runs, 0-255 where 0 is as slow as it can, 255 as fast as it can
  String Desc;
  unsigned long lastMillis;
};

#endif
