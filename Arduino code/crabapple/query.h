#ifndef query_h
#define query_h

// include types & constants of Wiring core API
#include <Arduino.h>

void readState(enum obj_state state) {
  if (state == DO) {
    Serial.println(F("DO"));
  }
  else if (state == DOING) {
    Serial.println(F("DOING"));
  }
  else if (state == DONE) {
    Serial.println(F("DONE"));
  }
}

void query_button(int index) { //this is whats returned from a query request 
  Serial.print(F("button"));
  Serial.println(index);
  Serial.print(F("Description: "));
  Serial.println(button_obj[index].Desc);
  Serial.print(F("status: "));
  readState(button_obj[index].do_me);
  Serial.println();
}

void query_buzzer(int index) { //this is whats returned from a query request 
  Serial.print(F("buzzer"));
  Serial.println(index);
  Serial.print(F("frequency: "));
  Serial.println(buzzer_obj[index].frequency);
  Serial.print(F("duration (ms): "));
  Serial.println(buzzer_obj[index].duration);
  Serial.print(F("status: "));
  readState(buzzer_obj[index].do_me);
  Serial.println();
}

void query_prog(int index) { //this is whats returned from a query request
  Serial.print(F("program"));
  Serial.println(index);
  Serial.print(F("Description: "));
  Serial.println(prgm_obj[index].Desc);
  Serial.print(F("timeout (s): "));
  Serial.println(prgm_obj[index].Timeout);
  Serial.print(F("status: "));
  readState(prgm_obj[index].do_me);
  Serial.println();
}

void query_light(int index) { //this is whats returned from a query request
  Serial.print(F("light"));
  Serial.println(index);
  Serial.print(F("Description: "));
  Serial.println(light_obj[index].Desc);
  Serial.print(F("default brightness: "));
  Serial.println(light_obj[index].default_brightness);
  Serial.print(F("current brightness: "));
  Serial.println(light_obj[index].brightness);
  Serial.print(F("timeout (s): "));
  Serial.println(light_obj[index].Timeout);
  Serial.print(F("status: "));
  readState(light_obj[index].do_me);
  Serial.println();
}

void query_motor(int index) { //this is whats returned from a query request
  Serial.print(F("motor"));
  Serial.println(index);
  Serial.print(F("Description: "));
  Serial.println(motor_obj[index].Desc);
  Serial.print(F("current speed: "));
  Serial.println(motor_obj[index].currentSpeed);
  Serial.print(F("current direction: "));
  Serial.println(motor_obj[index].Direction);
  Serial.print(F("Min/Max: "));
  Serial.print(motor_obj[index].Min);
  Serial.print(F("/"));
  Serial.println(motor_obj[index].Max);
  Serial.print(F("timeout (s): "));
  Serial.println(motor_obj[index].Timeout);
  Serial.print(F("rate 0,1-255: "));
  Serial.println(motor_obj[index].rate);
  Serial.print(F("status: "));
  readState(motor_obj[index].do_me);
  Serial.println();
}

void query_servo(int index) {
  Serial.print(F("servo"));
  Serial.println(index);
  Serial.print(F("Description: "));
  Serial.println(servo_obj[index].Desc);
  Serial.print(F("Min/Max: "));
  Serial.print(servo_obj[index].Min);
  Serial.print(F("/"));
  Serial.println(servo_obj[index].Max);
  Serial.print(F("home: "));
  Serial.println(servo_obj[index].Home);
  Serial.print(F("current position: "));
  Serial.println(servo_obj[index].currentPos);
  Serial.print(F("timeout (s): "));
  Serial.println(servo_obj[index].Timeout);
  Serial.print(F("rate 0,1-255: "));
  Serial.println(servo_obj[index].rate);
  Serial.print(F("status: "));
  readState(servo_obj[index].do_me);
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
  for (int i = 0; i < num_buzzers; i++) {
    query_buzzer(i);
  }
  for (int i = 0; i < num_programs; i++) {
    query_prog(i);
  }
}

#endif
