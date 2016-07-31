#ifndef init_h
#define init_h

// include types & constants of Wiring core API
#include <Arduino.h>


void initialise()
{
  Serial.begin(9600); //we use serial for our comms
  
  load_conf(); //load in the configuration for the parts you want to use
  query_config(); //print out the config

  for (byte i = 0; i < num_servos; i++) {
    servo_[i].attach(servo_obj[i].Pin);
    servo_[i].write(servo_obj[i].Home);
  }

  load_programs();

}

#endif
