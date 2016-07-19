#ifndef watchdog_h
#define watchdog_h

// include types & constants of Wiring core API
#include <Arduino.h>

void hardwareWrite() {

  //we look at the do_me flag of each object and do stuff to the objects that have it flagged. we then unflag it.

//we loop through objects of each type

  for (int i = 0; i < num_servos; i++) {
    if (servo_obj[i].do_me) {
      servo_[i].write(servo_obj[i].Pos);
      servo_obj[i].do_me = false; //do_me done so do_me no more
    }
  }
  
  for (int i = 0; i < num_motors; i++) {
    if (motor_obj[i].do_me) {
      if (motor_obj[i].Direction == 0) {
        digitalWrite(motor_obj[i].dirPin1, HIGH); //set direction anticlockwise
        digitalWrite(motor_obj[i].dirPin2, LOW);
      }
      else if (motor_obj[i].Direction == 1) {
        digitalWrite(motor_obj[i].dirPin1, LOW); //set direction clockwise
        digitalWrite(motor_obj[i].dirPin2, HIGH);
      }
      analogWrite(motor_obj[i].speedPin, motor_obj[i].Speed);
      motor_obj[i].do_me = false; //do_me done so do_me no more
    }
  }
  
  for (int i = 0; i < num_lights; i++) {
    if (light_obj[i].do_me) {
      analogWrite(light_obj[i].Pin, light_obj[i].brightness);
      light_obj[i].do_me = false; //do_me done so do_me no more
    }
  }
  
  for (int i = 0; i < num_buttons; i++) {
    if (button_obj[i].do_me) {
      //doButton(i, 0, DO_CMD);
      button_obj[i].do_me = false; //do_me done so do_me no more
    }  }
    
  for (int i = 0; i < num_programs; i++) {
    if (prgm_obj[i].do_me) {  
      (*programPtrs[i])(i); //calls the program at the index of `index` in the pointers array
      prgm_obj[i].do_me = false; //do_me done so do_me no more
    }
  }

  for (int i = 0; i < num_buzzers; i++) {
    if (buzzer_obj[i].do_me) {  
      tone(buzzer_obj[i].Pin, buzzer_obj[i].frequency, buzzer_obj[i].duration);
      buzzer_obj[i].do_me = false; //do_me done so do_me no more
    }
  }
}

#endif
