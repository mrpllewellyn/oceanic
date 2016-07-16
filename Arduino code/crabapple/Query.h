#ifndef Query_h
#define Query_h

// include types & constants of Wiring core API
#include <Arduino.h>

void query_servo(servo query) {
  Serial.println(query.Min);
  Serial.println(query.Max);
  Serial.println(query.Home);
  Serial.println(query.Pos);
  Serial.println(query.Timeout);
}

void query_motor(motor query) {
  Serial.println(query.Speed);
  Serial.println(query.Direction);
  Serial.println(query.Limit);
  Serial.println(query.Timeout);  
}

void query_light(light query) {
  Serial.println(query.default_brightness);
  Serial.println(query.brightness);
  Serial.println(query.Timeout);
}

void query_button(button query) {
  Serial.println(query.state);
  Serial.println(query.Timeout);
}



#endif
