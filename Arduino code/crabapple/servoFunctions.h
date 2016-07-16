#ifndef servoFunctions_h
#define servoFunctions_h

// include types & constants of Wiring core API
#include <Arduino.h>

void do_servo0(int value, char action) {
  if (action == DO_CMD){
    if (value <= servo0_data.Max && value >= servo0_data.Min){
      servo0_data.Pos = value;
      servo0.write(servo0_data.Pos);
    }
  }
  else if (action == QUERY_CMD){
    servo0_data.Pos = servo0.read();
    query_servo(servo0_data);
  }
  else if (action == SETTIMEOUT_CMD){
    servo0_data.Timeout = value;
  }
}
  
void do_servo1(int value, char action) {
  if (action == DO_CMD){
    if (value <= servo1_data.Max && value >= servo1_data.Min){
      servo1_data.Pos = value;
      servo1.write(servo1_data.Pos);
    }
  }
  else if (action == QUERY_CMD){
    servo1_data.Pos = servo1.read();
    query_servo(servo1_data);
  }
  else if (action == SETTIMEOUT_CMD){
    servo1_data.Timeout = value;
  }
}
  
void do_servo2(int value, char action) {
  if (action == DO_CMD){
    if (value <= servo2_data.Max && value >= servo2_data.Min){
      servo2_data.Pos = value;
      servo2.write(servo2_data.Pos);
    }
  }
  else if (action == QUERY_CMD){
    servo2_data.Pos = servo2.read();
    query_servo(servo2_data);
  }
  else if (action == SETTIMEOUT_CMD){
    servo2_data.Timeout = value;
  }
}
  
void do_servo3(int value, char action) {
  if (action == DO_CMD){
    if (value <= servo3_data.Max && value >= servo3_data.Min){
      servo3_data.Pos = value;
      servo3.write(servo3_data.Pos);
    }
  }
  else if (action == QUERY_CMD){
    servo3_data.Pos = servo3.read();
    query_servo(servo3_data);
  }
  else if (action == SETTIMEOUT_CMD){
    servo3_data.Timeout = value;
  }
}

#endif
