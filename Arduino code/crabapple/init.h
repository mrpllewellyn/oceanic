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

}

#endif
