#ifndef buttonFunctions_h
#define buttonFunctions_h

// include types & constants of Wiring core API
#include <Arduino.h>

void query_button(button query, int index) {
  Serial.print(F("button"));
  Serial.println(index);
  Serial.println(query.Desc);
  Serial.println(query.state);
  Serial.println(query.Timeout);
  Serial.println();
}

void doButton(int index, int value, char action) {

  if (action == DO_CMD) {
    if (!(digitalRead(buttondata[index].Pin))){
      buttondata[index].state = 1;
      Serial.print(F("button:"));
      Serial.print(index);
      Serial.println(F(" pressed"));
      buttondata[index].lastMillis = millis();
    }
    else {
      buttondata[index].state = 1;
    }
  }

  else if (action == QUERY_CMD) {
    buttondata[index].state = !(digitalRead(buttondata[index].Pin));
    query_button(buttondata[index], index);
  }

  else if (action == SETTIMEOUT_CMD) {
    buttondata[index].Timeout = value;
  }

}

#endif
