#ifndef watchdogs_h
#define watchdogs_h

// include types & constants of Wiring core API
#include <Arduino.h>

void check_timeouts() {
  for (int i = 0; i < num_servos; i++) {
    if ((millis() - servo_obj[i].lastMillis) > ((unsigned long) servo_obj[i].Timeout * 1000)) { //timeouts are stored in seconds so need to be multiplied by 1000 to make milliseconds
      doServo(i, servo_obj[i].Home, DO_CMD);                                                  //the timeout vars are temporalily 'cast' as unsigned long to accommodate the size
      servo_obj[i].isLocked = false;
      servo_obj[i].isActive = false;
    }//if a servo timesout then it returns to its home position
  }

  for (int i = 0; i < num_motors; i++) {
    if ((millis() - motor_obj[i].lastMillis) > ((unsigned long) motor_obj[i].Timeout * 1000)) {
      doMotor(i, 0, DO_CMD);
      motor_obj[i].isLocked = false;
      motor_obj[i].isActive = false;
    }//if a motor timesout then it speed is set to 0 
  }

  for (int i = 0; i < num_lights; i++) {
    if (light_obj[i].isActive == false  && light_obj[i].isLocked == true) {
      
      if ((millis() - light_obj[i].lastMillis) > ((unsigned long) light_obj[i].Timeout * 1000)) {
        Serial.println(F("timeout light"));
        doLight(i, light_obj[i].default_brightness, DO_CMD);
        light_obj[i].isLocked = false;
      }    
    }
  }

  for (int i = 0; i < num_buzzers; i++) { //no need to time out buttons at the moment
    if (buzzer_obj[i].isLocked == true) {
      
    if ((millis() - buzzer_obj[i].lastMillis) > (unsigned long) buzzer_obj[i].duration) {
      buzzer_obj[i].isLocked = false;
    }

    }
  }


  for (int i = 0; i < num_programs; i++) {
    if ((millis() - prgm_obj[i].lastMillis) > ((unsigned long) prgm_obj[i].Timeout * 1000)) {
      prgm_obj[i].isActive = false;
      prgm_obj[i].isLocked = false;      
    } 
  } 
}

void check_buttons() {
  for (int i = 0; i < num_buttons; i++) { //no need to time out buttons at the moment
    if (!(digitalRead(button_obj[i].Pin))){
      button_obj[i].isActive = true;
      Serial.print(F("button:"));
      Serial.print(i);
      Serial.println(F(" pressed"));
    }
    else {
      button_obj[i].isActive = false;
    }
  }
}

void check_servo_positions() {
  for (int i = 0; i < num_servos; i++) {
    //servo_obj[i].currentPos = servo_[i].read();
    if (servo_obj[i].lastMillis < (millis() - (255 / servo_obj[i].rate))) {
      if (servo_obj[i].currentPos < servo_obj[i].targetPos) {
        servo_obj[i].currentPos++;
        if (servo_obj[i].currentPos > servo_obj[i].Max) {
          servo_obj[i].currentPos = servo_obj[i].Max;
        }
        //servo_obj[i].isActive = true;
      }
      if (servo_obj[i].currentPos > servo_obj[i].targetPos) {
        servo_obj[i].currentPos--;
        if (servo_obj[i].currentPos < servo_obj[i].Min) {
          servo_obj[i].currentPos =  servo_obj[i].Min;
        }
        //servo_obj[i].isActive = true;
      }     
    }
  }
}

void check_motor_speed() {
  for (int i = 0; i < num_motors; i++) {
    if (motor_obj[i].lastMillis < (millis() - (255 / motor_obj[i].rate))) {
      if (motor_obj[i].currentSpeed < motor_obj[i].targetSpeed) {
        motor_obj[i].currentSpeed++;
        if (motor_obj[i].currentSpeed < motor_obj[i].Min) {
          motor_obj[i].currentSpeed = motor_obj[i].Min;
        }
        //motor_obj[i].do_me = DO;
      }
      if (motor_obj[i].currentSpeed > motor_obj[i].targetSpeed) {
        motor_obj[i].currentSpeed--;
        if (motor_obj[i].currentSpeed < motor_obj[i].Min) {
          motor_obj[i].currentSpeed = 0;
        }
        //motor_obj[i].do_me = DO;
      }     
    }
  }
}


void hardwareWrite() {

  //we look at the do_me flag of each object and do stuff to the objects that have it flagged. we then unflag it.

//we loop through objects of each type

  for (int i = 0; i < num_servos; i++) {
    if (servo_obj[i].isActive == true) {
      servo_[i].write(servo_obj[i].currentPos);
      servo_obj[i].lastMillis = millis();
      servo_obj[i].isLocked = true; 
    }
  }
  
  for (int i = 0; i < num_motors; i++) {
    if (motor_obj[i].isActive == true) {
      if (motor_obj[i].Direction == 0) {
        digitalWrite(motor_obj[i].dirPin1, HIGH); //set direction anticlockwise
        digitalWrite(motor_obj[i].dirPin2, LOW);
      }
      else if (motor_obj[i].Direction == 1) {
        digitalWrite(motor_obj[i].dirPin1, LOW); //set direction clockwise
        digitalWrite(motor_obj[i].dirPin2, HIGH);
      }
      analogWrite(motor_obj[i].speedPin, motor_obj[i].currentSpeed);
      motor_obj[i].lastMillis = millis();
      motor_obj[i].isLocked = true; 
    }
  }
  
  for (int i = 0; i < num_lights; i++) {
    if (light_obj[i].isActive == true) {
      analogWrite(light_obj[i].Pin, light_obj[i].brightness);
      light_obj[i].lastMillis = millis();
      light_obj[i].isActive = false;      
    }
  }
  
//  for (int i = 0; i < num_buttons; i++) {
//    if (button_obj[i].isActive == true) {
//      //doButton(i, 0, DO_CMD);
//      button_obj[i].isLocked = true;
//    }  }
    
  for (int i = 0; i < num_programs; i++) {
    if (prgm_obj[i].isActive == true) {  
      (*programPtrs[i])(i); //calls the program at the index of `index` in the pointers array
      prgm_obj[i].isLocked = true; 
    }
  }

  for (int i = 0; i < num_buzzers; i++) {
    if (buzzer_obj[i].isActive == true) {  
      tone(buzzer_obj[i].Pin, buzzer_obj[i].frequency, buzzer_obj[i].duration);
      buzzer_obj[i].lastMillis = millis();
      buzzer_obj[i].isActive = false; 
    }
  }
}

void watchdogs() {
  check_buttons();
  check_servo_positions();
  check_motor_speed();
  hardwareWrite();
  check_timeouts();
}

#endif
