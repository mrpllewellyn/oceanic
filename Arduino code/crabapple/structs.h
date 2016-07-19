#ifndef structs_h
#define structs_h

// include types & constants of Wiring core API
#include <Arduino.h>

struct servo { // struct for servo object type
  byte Pin;      // the number of the servo pin
  byte Min;     //servo min allowed position
  byte Max;     //servo max allowed position
  byte Home;    //servo default position
  unsigned int Timeout; //timeout
  String Desc; //object description
  byte currentPos;     //servo position
  byte targetPos;
  byte rate; //the speed the servo moves min0-255max
  unsigned long lastMillis; //record of when unit was last run
  boolean do_me; //flag that gets picked up in our main loop and tells the code that this object needs updating
};

struct motor {
  byte speedPin;      // the number of the pwm pin
  byte dirPin1;
  byte dirPin2;
  byte Limit;
  unsigned int Timeout;
  String Desc;
  byte rate; //the (de)accell of the motor min 0 max 255
  boolean Direction;
  byte currentSpeed;
  byte targetSpeed;
  unsigned long lastMillis;
  boolean do_me; //flag that gets picked up in our main loop and tells the code that this object needs updating
};

struct light {
  byte Pin;      // the number of the light pin
  byte default_brightness;
  unsigned int Timeout;
  String Desc;
  byte brightness;
  unsigned long lastMillis;
  boolean do_me; //flag that gets picked up in our main loop and tells the code that this object needs updating

};

struct button {
  byte Pin;
  String Desc;
  byte rate; //seems unintuitive but this could be used in the button debounce code (which doesn't actually exist)
  boolean state;
  boolean do_me; //flag that gets picked up in our main loop and tells the code that this object needs updating
};

struct buzzer {
  byte Pin;
  byte rate;
  boolean state;
  int frequency;
  unsigned int duration;
  boolean do_me;
};

struct prgm {
  unsigned int Timeout;
  String Desc;
  boolean state;
  unsigned long lastMillis;
  boolean do_me; //flag that gets picked up in our main loop and tells the code that this object needs updating
};

struct cmd {
  char obj_type;
  byte obj_number;
  char action_type;
  int value;
};

#endif
