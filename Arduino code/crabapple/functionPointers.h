#ifndef functionPointers_h
#define functionPointers_h

// include types & constants of Wiring core API
#include <Arduino.h>

void (*servoPtrs[num_servos])(int value, char action); //the array of servo function pointers
void (*motorPtrs[num_motors])(int value, char action); //the array of motor function pointers
void (*lightPtrs[num_lights])(int value, char action); //the array of light function pointers
void (*buttonPtrs[num_buttons])(int value, char action); //the array of button function pointers

void callServo(int index,int value, char action) {
  if (index < num_servos){
  (*servoPtrs[index])(value, action); //calls the function at the index of `num` in the array
  }
}

void callMotor(int index, int value, char action) {
  if (index < num_motors){
    (*motorPtrs[index])(value, action); //calls the function at the index of `index` in the array
  }
}

void callLight(int index, int value, char action) {
  if (index < num_lights){
    (*lightPtrs[index])(value, action); //calls the function at the index of `index` in the array
  }
}

void callButton(int index, int value, char action) {
  if (index < num_buttons){
    (*buttonPtrs[index])(value, action); //calls the function at the index of `index` in the array
  }
}

#endif
