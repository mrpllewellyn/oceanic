#ifndef programs_h
#define programs_h

// include types & constants of Wiring core API
#include <Arduino.h>

//int progcounter; //counter to test program loops
//int timebetweenloops;

void query_prog(prog query, int index) { //this is whats returned from a query request
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
      progdata[index].state = true; //sets run state to true, this is different from other object types that swich on/change objects directly. programTimer will handle running programs.
      progdata[index].lastMillis = millis();
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
  doMotor(0, 255, DO_CMD);
  doMotor(1, 255, DO_CMD);    
}

void go_backward(int i){ // prog1
  doMotor(0, -255, DO_CMD);
  doMotor(1, -255, DO_CMD);    
} 

void go_left(int i){} //prog2

void go_right(int i){} //prog3

void prog_test(int i){ //prog4
//  progcounter++;
//  if (progcounter > 30000){
//    int temp = (millis() - timebetweenloops);
//    temp = (temp / 30);
//    Serial.println(F("this line gets printed every 30000 runs while active"));
//    Serial.print(F("each loops takes: "));
//    Serial.print(temp);
//    Serial.println(F("microseconds"));
//    timebetweenloops = millis();
//    progcounter = 0;
//  }
} 


#endif
