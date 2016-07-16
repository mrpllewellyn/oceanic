#ifndef servoFunctions_h
#define servoFunctions_h

// include types & constants of Wiring core API
#include <Arduino.h>

void do_servo0(int value, char action) {
  if (action == DO_CMD){
    if (value <= servodata[0].Max && value >= servodata[0].Min){
      servodata[0].Pos = value;
      servo_[0].write(servodata[0].Pos);
    }
  }
  else if (action == QUERY_CMD){
    servodata[0].Pos = servo_[0].read();
    query_servo(servodata[0]);
  }
  else if (action == SETTIMEOUT_CMD){
    servodata[0].Timeout = value;
  }
}
  
void do_servo1(int value, char action) {
  if (action == DO_CMD){
    if (value <= servodata[1].Max && value >= servodata[1].Min){
      servodata[1].Pos = value;
      servo_[1].write(servodata[1].Pos);
    }
  }
  else if (action == QUERY_CMD){
    servodata[1].Pos = servo_[1].read();
    query_servo(servodata[1]);
  }
  else if (action == SETTIMEOUT_CMD){
    servodata[1].Timeout = value;
  }
}
  
void do_servo2(int value, char action) {
  if (action == DO_CMD){
    if (value <= servodata[2].Max && value >= servodata[2].Min){
      servodata[2].Pos = value;
      servo_[2].write(servodata[2].Pos);
    }
  }
  else if (action == QUERY_CMD){
    servodata[2].Pos = servo_[2].read();
    query_servo(servodata[2]);
  }
  else if (action == SETTIMEOUT_CMD){
    servodata[2].Timeout = value;
  }
}
  
void do_servo3(int value, char action) {
  if (action == DO_CMD){
    if (value <= servodata[3].Max && value >= servodata[3].Min){
      servodata[3].Pos = value;
      servo_[3].write(servodata[3].Pos);
    }
  }
  else if (action == QUERY_CMD){
    servodata[3].Pos = servo_[3].read();
    query_servo(servodata[3]);
  }
  else if (action == SETTIMEOUT_CMD){
    servodata[3].Timeout = value;
  }
}

#endif
