#ifndef watchdogs_h
#define watchdogs_h

// include types & constants of Wiring core API
#include <Arduino.h>

void check_timeouts() {
  for (int i = 0; i < num_servos; i++) {
    if ((millis() - servo_obj[i].lastMillis) > ((unsigned long) servo_obj[i].Timeout * 1000)) { //timeouts are stored in seconds so need to be multiplied by 1000 to make milliseconds
      doServo(i, servo_obj[i].Home, DO_CMD);                                                    //the timeout vars are temporalily 'cast' as unsigned long to accommodate the size
    }//if a servo timesout then it returns to its home position
  }

  for (int i = 0; i < num_motors; i++) {
    if ((millis() - motor_obj[i].lastMillis) > ((unsigned long) motor_obj[i].Timeout * 1000)) {
      doMotor(i, 0, DO_CMD);
    }//if a motor timesout then it speed is set to 0 
  }

  for (int i = 0; i < num_lights; i++) {
    if ((millis() - light_obj[i].lastMillis) > ((unsigned long) light_obj[i].Timeout * 1000)) {
      doLight(i, light_obj[i].default_brightness, DO_CMD);
    }//light returns to default brightness when it timesout
  }

//  for (int i = 0; i < num_buttons; i++) { //no need to time out buttons at the moment
//    if ((millis() - button_obj[i].lastMillis) > ((unsigned long) button_obj[i].Timeout * 1000)) {
//      doButton(i, 0, DO_CMD); //checks button state at timeout
//    }
//  }


  for (int i = 0; i < num_programs; i++) {
    if ((millis() - prgm_obj[i].lastMillis) > ((unsigned long) prgm_obj[i].Timeout * 1000)) {
      prgm_obj[i].state = false;
    } 
  } 
}

void check_buttons() {
  for (int i = 0; i < num_buttons; i++) { //no need to time out buttons at the moment
    if (!(digitalRead(button_obj[i].Pin))){
      button_obj[i].state = 1;
      Serial.print(F("button:"));
      Serial.print(i);
      Serial.println(F(" pressed"));
    }
    else {
      button_obj[i].state = 0;
    }
  }
}

void watchdogs() {
  check_timeouts();
  check_buttons();
}

#endif
