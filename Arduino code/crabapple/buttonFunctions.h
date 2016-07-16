#ifndef buttonFunctions_h
#define buttonFunctions_h

// include types & constants of Wiring core API
#include <Arduino.h>

void do_button0(int value, char action) {
  if (action == DO_CMD){

  }
  else if (action == QUERY_CMD){
    button0_data.state = !(digitalRead(button0_data.Pin));
    query_button(button0_data);
  }
  else if (action == SETTIMEOUT_CMD){
    button0_data.Timeout = value;
  }  
}

void do_button1(int value, char action) {
  if (action == DO_CMD){

  }
  else if (action == QUERY_CMD){
    button1_data.state = !(digitalRead(button1_data.Pin));
    query_button(button1_data);
  }
  else if (action == SETTIMEOUT_CMD){
    button1_data.Timeout = value;
  }  
}


#endif
