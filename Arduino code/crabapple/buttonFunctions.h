#ifndef buttonFunctions_h
#define buttonFunctions_h

// include types & constants of Wiring core API
#include <Arduino.h>

void do_button0(int value, char action) {
  if (action == DO_CMD){

  }
  else if (action == QUERY_CMD){
    buttondata[0].state = !(digitalRead(buttondata[0].Pin));
    query_button(buttondata[0]);
  }
  else if (action == SETTIMEOUT_CMD){
    buttondata[0].Timeout = value;
  }  
}

void do_button1(int value, char action) {
  if (action == DO_CMD){

  }
  else if (action == QUERY_CMD){
    buttondata[1].state = !(digitalRead(buttondata[1].Pin));
    query_button(buttondata[1]);
  }
  else if (action == SETTIMEOUT_CMD){
    buttondata[1].Timeout = value;
  }  
}


#endif
