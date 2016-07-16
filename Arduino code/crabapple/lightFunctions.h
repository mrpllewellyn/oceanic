#ifndef lightFunctions_h
#define lightFunctions_h

// include types & constants of Wiring core API
#include <Arduino.h>

void do_light0(int value, char action) {
  if (action == DO_CMD){
    analogWrite(lightdata[0].Pin, value);
    lightdata[0].brightness = value;
  }
  else if (action == QUERY_CMD){
    query_light(lightdata[0]);
  }
  else if (action == SETTIMEOUT_CMD){
    lightdata[0].Timeout = value;
  }  
}


#endif
