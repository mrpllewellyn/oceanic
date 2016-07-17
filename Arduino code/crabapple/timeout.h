#ifndef timeout_h
#define timeout_h

// include types & constants of Wiring core API
#include <Arduino.h>

void check_timeouts() {
  for (int i = 0; i < num_servos; i++) {
    if ((millis() - servodata[i].lastMillis) > servodata[i].Timeout) {
      doServo(i, servodata[i].Home, DO_CMD);
    }
  }

  for (int i = 0; i < num_motors; i++) {
    if ((millis() - motordata[i].lastMillis) > motordata[i].Timeout) {
      doMotor(i, 0, DO_CMD);
    }
  }

  for (int i = 0; i < num_lights; i++) {
    if ((millis() - lightdata[i].lastMillis) > lightdata[i].Timeout) {
      doLight(i, lightdata[i].default_brightness, DO_CMD);
    }
  }

  for (int i = 0; i < num_buttons; i++) {
    if ((millis() - buttondata[i].lastMillis) > buttondata[i].Timeout) {
      doButton(i, 0, DO_CMD); //checks button state at timeout
    }
  }
}

#endif
