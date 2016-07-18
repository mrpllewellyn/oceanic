#ifndef watchdog_h
#define watchdog_h

// include types & constants of Wiring core API
#include <Arduino.h>

void hardwareWrite() {

  //we look at the do_me flag of each object and do stuff to the objects that have it flagged. we then unflag it.

//we loop through objects of each type

  for (int i = 0; i < num_servos; i++) {
    if (servodata[i].do_me) {
      servo_[i].write(servodata[i].Pos);
      servodata[i].do_me = false; //do_me done so do_me no more
    }
  }
  
  for (int i = 0; i < num_motors; i++) {
    if (motordata[i].do_me) {
      if (motordata[i].Direction == 0) {
        digitalWrite(motordata[i].dirPin1, HIGH); //set direction anticlockwise
        digitalWrite(motordata[i].dirPin2, LOW);
      }
      else if (motordata[i].Direction == 1) {
        digitalWrite(motordata[i].dirPin1, LOW); //set direction clockwise
        digitalWrite(motordata[i].dirPin2, HIGH);
      }
      analogWrite(motordata[i].speedPin, motordata[i].Speed);
      motordata[i].do_me = false; //do_me done so do_me no more
    }
  }
  
  for (int i = 0; i < num_lights; i++) {
    if (lightdata[i].do_me) {
      analogWrite(lightdata[i].Pin, lightdata[i].brightness);
      lightdata[i].do_me = false; //do_me done so do_me no more
    }
  }
  
  for (int i = 0; i < num_buttons; i++) {
    if (buttondata[i].do_me) {
      //doButton(i, 0, DO_CMD);
      buttondata[i].do_me = false; //do_me done so do_me no more
    }  }
    
  for (int i = 0; i < num_programs; i++) {
    if (progdata[i].do_me) {  
      (*programPtrs[i])(i); //calls the program at the index of `index` in the pointers array
      progdata[i].do_me = false; //do_me done so do_me no more
    }
  }
}

#endif
