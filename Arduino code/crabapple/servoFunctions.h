#ifndef servoFunctions_h
#define servoFunctions_h

// include types & constants of Wiring core API
#include <Arduino.h>

void doServo(int index, int value, char action) {

  if (action == DO_CMD) {
    if (value <= servodata[index].Max && value >= servodata[index].Min) {
      servodata[index].Pos = value;
      servo_[index].write(servodata[index].Pos);
      servodata[index].lastMillis = millis();
    }
  }

  else if (action == QUERY_CMD) {
    servodata[index].Pos = servo_[index].read();
    query_servo(servodata[index]);
  }

  else if (action == SETTIMEOUT_CMD) {
    servodata[index].Timeout = value;
  }

}

#endif
