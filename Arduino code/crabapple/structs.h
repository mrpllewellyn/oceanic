#ifndef structs_h
#define structs_h

// include types & constants of Wiring core API
#include <Arduino.h>

typedef enum obj_state {
  DONE,
  DO,
  DOING
};
extern uint8_t obj_state;



struct cmd {
  char obj_type;
  byte obj_number;
  char action_type;
  int value;
  boolean pending;
};

struct servo { // struct for servo object type
  byte Pin;      // the number of the servo pin
  byte Min;     //servo min allowed position
  byte Max;     //servo max allowed position
  byte Home;    //servo default position
  unsigned int Timeout; //timeout
  String Desc; //object description
  byte rate; //the speed the servo moves slowest 1-255 fastest, however rate of 0 = run as fast as I can 
  byte currentPos;     //servo position
  byte targetPos;
  unsigned long lastMillis; //record of when unit was last run
  enum obj_state do_me; //flag that gets picked up in our main loop and tells the code that this object needs updating
};

struct motor {
  byte speedPin;      // the number of the pwm pin
  byte dirPin1;
  byte dirPin2;
  byte Min;
  byte Max;
  unsigned int Timeout;
  String Desc;
  byte rate; //the (de)accell of the motor slowest 1 fastest 255, however rate of 0 = run as fast as I can
  boolean Direction;
  byte currentSpeed;
  byte targetSpeed;
  unsigned long lastMillis;
  enum obj_state do_me; //flag that gets picked up in our main loop and tells the code that this object needs updating
};

struct light {
  byte Pin;      // the number of the light pin
  byte default_brightness;
  unsigned int Timeout;
  String Desc;
  byte brightness;
  unsigned long lastMillis;
  enum obj_state do_me; //flag that gets picked up in our main loop and tells the code that this object needs updating

};

struct button {
  byte Pin;
  String Desc;
  enum obj_state do_me; //flag that gets picked up in our main loop and tells the code that this object needs updating
};

struct buzzer {
  byte Pin;
  int frequency;
  unsigned int duration;
  enum obj_state do_me;
};

struct prgm {
  unsigned int Timeout;
  String Desc;
  unsigned long lastMillis;
  enum obj_state do_me; //flag that gets picked up in our main loop and tells the code that this object needs updating
};



#endif
