#ifndef customPrograms_h
#define customPrograms_h

// include types & constants of Wiring core API
#include <Arduino.h>

//int progcounter; //counter to test program loops
//int timebetweenloops;


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
