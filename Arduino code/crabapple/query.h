#ifndef query_h
#define query_h

// include types & constants of Wiring core API
#include <Arduino.h>

void query_button(int index) { //this is whats returned from a query request 
  Serial.print(F("button"));
  Serial.println(index);
  Serial.println(buttondata[index].Desc);
  Serial.println(buttondata[index].state);
  Serial.println(buttondata[index].Timeout);
  Serial.println();
}

void query_prog(int index) { //this is whats returned from a query request
  Serial.print(F("program"));
  Serial.println(index);
  Serial.println(progdata[index].Desc);
  Serial.println(progdata[index].state);
  Serial.println(progdata[index].Timeout);
  Serial.println();
}

void query_light(int index) { //this is whats returned from a query request
  Serial.print(F("light"));
  Serial.println(index);
  Serial.println(lightdata[index].Desc);
  Serial.println(lightdata[index].default_brightness);
  Serial.println(lightdata[index].brightness);
  Serial.println(lightdata[index].Timeout);
  Serial.println();
}

void query_motor(int index) { //this is whats returned from a query request
  Serial.print(F("motor"));
  Serial.println(index);
  Serial.println(motordata[index].Desc);
  Serial.println(motordata[index].Speed);
  Serial.println(motordata[index].Direction);
  Serial.println(motordata[index].Limit);
  Serial.println(motordata[index].Timeout);
  Serial.println();
}

void query_servo(int index) {
  Serial.print(F("servo"));
  Serial.println(index);
  Serial.println(servodata[index].Desc);
  Serial.println(servodata[index].Min);
  Serial.println(servodata[index].Max);
  Serial.println(servodata[index].Home);
  Serial.println(servodata[index].Pos);
  Serial.println(servodata[index].Timeout);
  Serial.println();
}

void query_all() {
  for (int i = 0; i < num_servos; i++) {
    query_servo(i);
  }
  for (int i = 0; i < num_motors; i++) {
    query_motor(i);
  }
  for (int i = 0; i < num_lights; i++) {
    query_light(i);
  }
  for (int i = 0; i < num_buttons; i++) {
    query_button(i);
  }
  for (int i = 0; i < num_programs; i++) {
    query_prog(i);
  }
}

#endif
