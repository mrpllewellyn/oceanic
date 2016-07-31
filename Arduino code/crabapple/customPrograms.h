#ifndef customPrograms_h
#define customPrograms_h

// include types & constants of Wiring core API
#include <Arduino.h>


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

void prgm_test(int i){ //prog4
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

void load_programs() {
programPtrs[0] = go_forward; //this declares the array of fucntion pointers
programPtrs[1] = go_backward; //each one points to a custom function that can be called through external commands
programPtrs[2] = go_left;     //the number of pointers declared should match num_programs in conf.h
programPtrs[3] = go_right;
programPtrs[4] = prgm_test;
}



#endif
