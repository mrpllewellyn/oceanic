#ifndef motorFucntions_h
#define motorFucntions_h

// include types & constants of Wiring core API
#include <Arduino.h>

void setMotorDirection(boolean Direction, byte pin1, byte pin2) {
  if (Direction == 0) {
    digitalWrite(pin1, HIGH); //set direction anticlockwise
    digitalWrite(pin2, LOW);
  }
  else if (Direction == 1) {
    digitalWrite(pin1, LOW); //set direction clockwise
    digitalWrite(pin2, HIGH);
  }
}

void driveMotor(byte duty, byte pin) {
  analogWrite(pin, duty);
}

void doMotor(int index, int value, char action) {

  if (action == DO_CMD) {
    if (value < 0) {
      motordata[index].Direction = 0; //go backwards
      value = value * -1;
    }
    else {
      motordata[index].Direction = 1; //go forwards
    }
    setMotorDirection(motordata[index].Direction, motordata[index].dirPin1, motordata[index].dirPin2);
    if (value <= motordata[index].Limit && value >= 0) {
      motordata[index].Speed = value;
      driveMotor(value, motordata[index].speedPin);
      motordata[index].lastMillis = millis();
    }
  }

  else if (action == QUERY_CMD) {
    query_motor(motordata[index]);
  }

  else if (action == SETTIMEOUT_CMD) {
    motordata[index].Timeout = value;
  }

}

#endif
