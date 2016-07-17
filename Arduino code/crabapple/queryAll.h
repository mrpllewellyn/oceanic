#ifndef queryAll_h
#define queryAll_h

// include types & constants of Wiring core API
#include <Arduino.h>

void query_all() {
  for (int i = 0; i < num_servos; i++) {
    Serial.print(F("servo:"));
    Serial.println(i);
    doServo(i, 0, QUERY_CMD);
    Serial.println();
  }
  for (int i = 0; i < num_motors; i++) {
    Serial.print(F("motor:"));
    Serial.println(i);
    doMotor(i, 0, QUERY_CMD);
    Serial.println();
  }
  for (int i = 0; i < num_lights; i++) {
    Serial.print(F("light:"));
    Serial.println(i);
    doLight(i, 0, QUERY_CMD);
    Serial.println();
  }
  for (int i = 0; i < num_buttons; i++) {
    Serial.print(F("button:"));
    Serial.println(i);
    doButton(i, 0, QUERY_CMD);
    Serial.println();
  }
}

#endif
