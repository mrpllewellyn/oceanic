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
      motordata[0].Direction = 0; //go backwards
      value = value * -1;
    }
    else {
      motordata[0].Direction = 1; //go forwards
    }
    set_motor_direction(motordata[0].Direction, motordata[0].dirPin1, motordata[0].dirPin2);
    if (value <= motordata[0].Limit && value >= 0){
      motordata[0].Speed = value;
      drive_motor(value, motordata[0].speedPin);
    }
  }
  
  else if (action == QUERY_CMD){
    query_motor(motordata[0]);
  }
  
  else if (action == SETTIMEOUT_CMD){
    motordata[0].Timeout = value;
  }
  
}

void do_motor1(int value, char action) {
  
  if (action == DO_CMD){
    if (value < 0){
      motordata[1].Direction = 0; //go backwards
      value = value * -1;
    }
    else {
      motordata[1].Direction = 1; //go forwards
    }
    set_motor_direction(motordata[1].Direction, motordata[1].dirPin1, motordata[1].dirPin2);
    if (value <= motordata[0].Limit && value >= 0){
      motordata[1].Speed = value;
      drive_motor(value, motordata[1].speedPin);
    }
  }
  
  else if (action == QUERY_CMD){
    query_motor(motordata[1]);
  }
  
  else if (action == SETTIMEOUT_CMD){
    motordata[1].Timeout = value;
  }
  
}


#endif
