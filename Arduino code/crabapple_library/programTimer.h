#ifndef programTimer_h
#define programTimer_h

// include types & constants of Wiring core API
#include <Arduino.h>

void program_timer() {
//checks for programs that have the on state and run their function
  for (int i = 0; i < num_programs; i++) {
    if (progdata[i].state) {
      (*programPtrs[i])(i); //calls the program at the index of `index` in the pointers array
    }
  }}

#endif
