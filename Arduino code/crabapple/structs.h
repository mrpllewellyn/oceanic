#ifndef structs_h
#define structs_h

// include types & constants of Wiring core API
#include <Arduino.h>

struct servo {
    byte Pin;      // the number of the servo pin
    byte Min;
    byte Max;
    byte Home;
    byte Pos;
    unsigned int Timeout;
    unsigned long lastMillis;
};

struct motor {
    byte speedPin;      // the number of the pwm pin
    byte dirPin1;
    byte dirPin2;
    byte Speed;
    byte Limit;
    boolean Direction;
    unsigned int Timeout;
    unsigned long lastMillis;
};

struct light {
    byte Pin;      // the number of the light pin
    byte default_brightness;
    byte brightness;
    unsigned int Timeout;
    unsigned long lastMillis;
};

struct cmd {
    char obj_type;
    byte obj_number;
    char action_type;
    int value;  
};


#endif
