#ifndef queryAll_h
#define queryAll_h

// include types & constants of Wiring core API
#include <Arduino.h>

void query_all() {
  for (int i = 0; i < num_servos; i++) {
    doServo(i, 0, QUERY_CMD);
  }
  for (int i = 0; i < num_motors; i++) {
    doMotor(i, 0, QUERY_CMD);
  }
  for (int i = 0; i < num_lights; i++) {
    doLight(i, 0, QUERY_CMD);
  }
  for (int i = 0; i < num_buttons; i++) {
    doButton(i, 0, QUERY_CMD);
  }
  for (int i = 0; i < num_programs; i++) {
    doProgram(i, 0, QUERY_CMD);
  }
}

#endif
