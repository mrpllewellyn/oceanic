#ifndef programs_h
#define programs_h

// include types & constants of Wiring core API
#include <Arduino.h>

void query_prog(prog query, int index) {
  Serial.print(F("program"));
  Serial.println(index);
  Serial.println(query.Desc);
  Serial.println(query.state);
  Serial.println(query.Timeout);
  Serial.println();
}

void doProgram(int index, int value, char action) {
  
  if (action == DO_CMD) {
    if (index < num_programs){
      (*programPtrs[index])(index); //calls the program at the index of `index` in the pointers array
    }
  
  }

  else if (action == QUERY_CMD) {
    query_prog(progdata[index], index);
  }

  else if (action == SETTIMEOUT_CMD) {
    progdata[index].Timeout = value;
  }
}

void go_forward(int i){ // prog0
  progdata[i].lastMillis = millis();
  while ((millis() - progdata[i].lastMillis) < progdata[i].Timeout){
    doMotor(0, 255, DO_CMD);
    doMotor(1, 255, DO_CMD);    
  }
}

void go_backward(int i){ // prog1
  progdata[i].lastMillis = millis();
  while ((millis() - progdata[i].lastMillis) < progdata[i].Timeout){
    doMotor(0, -255, DO_CMD);
    doMotor(1, -255, DO_CMD);    
  }
} 

void go_left(int i){} //prog2

void go_right(int i){} //prog3

void bumper_test(int i){} //prog4


#endif
