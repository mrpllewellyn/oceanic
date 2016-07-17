#ifndef init_h
#define init_h

// include types & constants of Wiring core API
#include <Arduino.h>


void initfoo()
{
  load_conf();

  for (int i = 0; i < num_servos; i++) {
    servo_[i].attach(servodata[i].Pin);
    servo_[i].write(servodata[i].Home);
  }

  programPtrs[0] = go_forward; //initializes the array
  programPtrs[1] = go_backward;
  programPtrs[2] = go_left;
  programPtrs[3] = go_right;
  programPtrs[4] = bumper_test;

}

#endif
