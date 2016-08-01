#ifndef query_h
#define query_h

// include types & constants of Wiring core API
#include <Arduino.h>

void query_config() {
  Serial.println(F("--- Objects ---"));
  Serial.print(F("#servos:"));
  Serial.println(num_servos);
  Serial.print(F("#motors:"));
  Serial.println(num_motors);
  Serial.print(F("#lights:"));
  Serial.println(num_lights);
  Serial.print(F("#buzzers:"));
  Serial.println(num_buzzers);
  Serial.print(F("#buttons:"));
  Serial.println(num_buttons);
  Serial.print(F("#programs:"));
  Serial.println(num_programs);
  Serial.println(F("--- Identifiers ---"));
  Serial.print(F("servo:"));
  Serial.println(SERVO_CMD);
  Serial.print(F("motor:"));
  Serial.println(MOTOR_CMD);
  Serial.print(F("light:"));
  Serial.println(LIGHT_CMD);
  Serial.print(F("buzzers:"));
  Serial.println(BUZZER_CMD);
  Serial.print(F("buttons:"));
  Serial.println(BUTTON_CMD);
  Serial.print(F("programs:"));
  Serial.println(PROG_CMD);
  Serial.println(F("--- Commands ---"));
  Serial.print(F("query:"));
  Serial.println(QUERY_CMD);
  Serial.print(F("do:"));
  Serial.println(DO_CMD);
  Serial.print(F("set timeout:"));
  Serial.println(SETTIMEOUT_CMD);
  Serial.print(F("set rate:"));
  Serial.println(SETRATE_CMD);
  Serial.print(F("reset:"));
  Serial.println(RESET_CMD);
  Serial.print(F("command Q length:"));
  Serial.println(CMD_BUFFER_SIZE);
}

void query_button(byte index) { //this is whats returned from a query request 
  Serial.print(F("button"));
  Serial.println(index);
  Serial.print(F("Description: "));
  Serial.println(button_obj[index].Desc);
//  Serial.print(F("status: "));
//  readState(button_obj[index].do_me);
  Serial.println();
}

void query_buzzer(byte index) { //this is whats returned from a query request 
  Serial.print(F("buzzer"));
  Serial.println(index);
  Serial.print(F("frequency: "));
  Serial.println(buzzer_obj[index].frequency);
  Serial.print(F("duration (ms): "));
  Serial.println(buzzer_obj[index].duration);
//  Serial.print(F("status: "));
//  readState(buzzer_obj[index].do_me);
  Serial.println();
}

void query_prog(byte index) { //this is whats returned from a query request
  Serial.print(F("program"));
  Serial.println(index);
  Serial.print(F("Description: "));
  Serial.println(prgm_obj[index].Desc);
  Serial.print(F("timeout (s): "));
  Serial.println(prgm_obj[index].Timeout);
//  Serial.print(F("status: "));
//  readState(prgm_obj[index].do_me);
  Serial.println();
}

void query_light(byte index) { //this is whats returned from a query request
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
  Serial.print(F("locked: "));
  Serial.println(light_obj[index].isRunning);  
  Serial.println();
}

void query_motor(byte index) { //this is whats returned from a query request
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
//  Serial.print(F("status: "));
//  readState(motor_obj[index].do_me);
  Serial.println();
}

void query_servo(byte index) {
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
//  Serial.print(F("status: "));
//  readState(servo_obj[index].do_me);
  Serial.println();
}

void query_all() {
  for (byte i = 0; i < num_servos; i++) {
    query_servo(i);
  }
  for (byte i = 0; i < num_motors; i++) {
    query_motor(i);
  }
  for (byte i = 0; i < num_lights; i++) {
    query_light(i);
  }
  for (byte i = 0; i < num_buttons; i++) {
    query_button(i);
  }
  for (byte i = 0; i < num_buzzers; i++) {
    query_buzzer(i);
  }
  for (byte i = 0; i < num_programs; i++) {
    query_prog(i);
  }
}

#endif
