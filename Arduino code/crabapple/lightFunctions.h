#ifndef lightFunctions_h
#define lightFunctions_h

// include types & constants of Wiring core API
#include <Arduino.h>

void do_light0(int value, char action) {
  if (action == DO_CMD){
    analogWrite(light0_data.Pin, value);
    light0_data.brightness = value;
  }
  else if (action == QUERY_CMD){
    query_light(light0_data);
  }
  else if (action == SETTIMEOUT_CMD){
    light0_data.Timeout = value;
  }  
}


#endif
