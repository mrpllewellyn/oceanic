#ifndef lightFunctions_h
#define lightFunctions_h

// include types & constants of Wiring core API
#include <Arduino.h>

void do_light0(int value, char action) {
  if (action == DO_CMD){

  }
  else if (action == QUERY_CMD){
    query_light(light0_data);
  }
  else if (action == SETTIMEOUT_CMD){
    light0_data.Timeout = value;
  }  
}


#endif
