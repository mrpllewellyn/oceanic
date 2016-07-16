#ifndef motorFucntions_h
#define motorFucntions_h

// include types & constants of Wiring core API
#include <Arduino.h>

void set_motor_direction(boolean Direction, byte pin1, byte pin2){
  if (Direction == 0) {
    digitalWrite(pin1,HIGH);//set direction anticlockwise
    digitalWrite(pin2,LOW);
  }
  else if (Direction == 1) {
    digitalWrite(pin1,LOW);//set direction clockwise
    digitalWrite(pin2,HIGH);
  }
}

void drive_motor(byte duty, byte pin){
  analogWrite(pin, duty);
}

void do_motor0(int value, char action) {
  
  if (action == DO_CMD){
    if (value < 0){
      motor0_data.Direction = 0; //go backwards
      value = value * -1;
    }
    else {
      motor0_data.Direction = 1; //go forwards
    }
    set_motor_direction(motor0_data.Direction, motor0_data.dirPin1, motor0_data.dirPin2);
    if (value <= motor0_data.Limit && value >= 0){
      motor0_data.Speed = value;
      drive_motor(value, motor0_data.speedPin);
    }
  }
  
  else if (action == QUERY_CMD){
    query_motor(motor0_data);
  }
  
  else if (action == SETTIMEOUT_CMD){
    motor0_data.Timeout = value;
  }
  
}

void do_motor1(int value, char action) {
  
  if (action == DO_CMD){
    if (value < 0){
      motor1_data.Direction = 0; //go backwards
      value = value * -1;
    }
    else {
      motor1_data.Direction = 1; //go forwards
    }
    set_motor_direction(motor1_data.Direction, motor1_data.dirPin1, motor1_data.dirPin2);
    if (value <= motor0_data.Limit && value >= 0){
      motor1_data.Speed = value;
      drive_motor(value, motor1_data.speedPin);
    }
  }
  
  else if (action == QUERY_CMD){
    query_motor(motor1_data);
  }
  
  else if (action == SETTIMEOUT_CMD){
    motor1_data.Timeout = value;
  }
  
}


#endif
