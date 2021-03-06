#ifndef timeout_h
#define timeout_h

// include types & constants of Wiring core API
#include <Arduino.h>

void check_timeouts() {
  for (int i = 0; i < num_servos; i++) {
    if ((millis() - servodata[i].lastMillis) > ((unsigned long) servodata[i].Timeout * 1000)) { //timeouts are stored in seconds so need to be multiplied by 1000 to make milliseconds
      doServo(i, servodata[i].Home, DO_CMD);                                                    //the timeout vars are temporalily 'cast' as unsigned long to accommodate the size
    }//if a servo timesout then it returns to its home position
  }

  for (int i = 0; i < num_motors; i++) {
    if ((millis() - motordata[i].lastMillis) > ((unsigned long) motordata[i].Timeout * 1000)) {
      doMotor(i, 0, DO_CMD);
    }//if a motor timesout then it speed is set to 0 
  }

  for (int i = 0; i < num_lights; i++) {
    if ((millis() - lightdata[i].lastMillis) > ((unsigned long) lightdata[i].Timeout * 1000)) {
      doLight(i, lightdata[i].default_brightness, DO_CMD);
    }//light returns to default brightness when it timesout
  }

  for (int i = 0; i < num_buttons; i++) {
    if ((millis() - buttondata[i].lastMillis) > ((unsigned long) buttondata[i].Timeout * 1000)) {
      doButton(i, 0, DO_CMD); //checks button state at timeout
    }
  }

  for (int i = 0; i < num_programs; i++) {
    if ((millis() - progdata[i].lastMillis) > ((unsigned long) progdata[i].Timeout * 1000)) {
      progdata[i].state = false;
    } //behaves differently to other object types and just changes state property, they should prob all do it this way however
  }
  
}

#endif
