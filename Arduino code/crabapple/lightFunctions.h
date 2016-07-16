#ifndef lightFunctions_h
#define lightFunctions_h

// include types & constants of Wiring core API
#include <Arduino.h>

void doLight(int index, int value, char action) {
  
  if (action == DO_CMD){
    analogWrite(lightdata[index].Pin, value);
    lightdata[index].brightness = value;
    lightdata[index].lastMillis = millis();
  }
  
  else if (action == QUERY_CMD){
    query_light(lightdata[index]);
  }
  
  else if (action == SETTIMEOUT_CMD){
    lightdata[index].Timeout = value;
  }  
  
}

#endif
