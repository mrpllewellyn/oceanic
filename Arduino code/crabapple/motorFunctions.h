#ifndef motorFucntions_h
#define motorFucntions_h

// include types & constants of Wiring core API
#include <Arduino.h>


void do_motor0(int value, char action) {
  if (action == DO_CMD){

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

  }
  else if (action == QUERY_CMD){
    query_motor(motor1_data);
  }
  else if (action == SETTIMEOUT_CMD){
    motor1_data.Timeout = value;
  }
}


#endif
