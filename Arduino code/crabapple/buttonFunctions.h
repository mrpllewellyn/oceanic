#ifndef buttonFunctions_h
#define buttonFunctions_h

// include types & constants of Wiring core API
#include <Arduino.h>

void doButton(int index, int value, char action) {

  if (action == DO_CMD) {
    buttondata[index].lastMillis = millis();
  }

  else if (action == QUERY_CMD) {
    buttondata[index].state = !(digitalRead(buttondata[index].Pin));
    query_button(buttondata[index]);
  }

  else if (action == SETTIMEOUT_CMD) {
    buttondata[index].Timeout = value;
  }

}

#endif
