#ifndef query_h
#define query_h

// include types & constants of Wiring core API
#include <Arduino.h>

void query_button(int index) { //this is whats returned from a query request 
  Serial.print(F("button"));
  Serial.println(index);
  Serial.println(button_obj[index].Desc);
  Serial.println(button_obj[index].state);
  Serial.println();
}

void query_buzzer(int index) { //this is whats returned from a query request 
  Serial.print(F("buzzer"));
  Serial.println(index);
  Serial.println(buzzer_obj[index].frequency);
  Serial.println(buzzer_obj[index].state);
  Serial.println(buzzer_obj[index].duration);
  Serial.println();
}

void query_prog(int index) { //this is whats returned from a query request
  Serial.print(F("program"));
  Serial.println(index);
  Serial.println(prgm_obj[index].Desc);
  Serial.println(prgm_obj[index].state);
  Serial.println(prgm_obj[index].Timeout);
  Serial.println();
}

void query_light(int index) { //this is whats returned from a query request
  Serial.print(F("light"));
  Serial.println(index);
  Serial.println(light_obj[index].Desc);
  Serial.println(light_obj[index].default_brightness);
  Serial.println(light_obj[index].brightness);
  Serial.println(light_obj[index].Timeout);
  Serial.println();
}

void query_motor(int index) { //this is whats returned from a query request
  Serial.print(F("motor"));
  Serial.println(index);
  Serial.println(motor_obj[index].Desc);
  Serial.println(motor_obj[index].Speed);
  Serial.println(motor_obj[index].Direction);
  Serial.println(motor_obj[index].Limit);
  Serial.println(motor_obj[index].Timeout);
  Serial.println();
}

void query_servo(int index) {
  Serial.print(F("servo"));
  Serial.println(index);
  Serial.println(servo_obj[index].Desc);
  Serial.println(servo_obj[index].Min);
  Serial.println(servo_obj[index].Max);
  Serial.println(servo_obj[index].Home);
  Serial.println(servo_obj[index].Pos);
  Serial.println(servo_obj[index].Timeout);
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
