#ifndef init_h
#define init_h

// include types & constants of Wiring core API
#include <Arduino.h>


void initfoo()
{
  servoPtrs[0] = do_servo0; //initializes the arrays
  servoPtrs[1] = do_servo1;
  servoPtrs[2] = do_servo2;
  servoPtrs[3] = do_servo3;

  motorPtrs[0] = do_motor0; 
  motorPtrs[1] = do_motor1;

  lightPtrs[0] = do_light0; 
  
  servo0.attach(servo0_data.Pin);
  servo1.attach(servo1_data.Pin);
  servo2.attach(servo2_data.Pin);
  servo3.attach(servo3_data.Pin); 
  servo0.write(servo0_data.Home);
  servo1.write(servo1_data.Home);
  servo2.write(servo2_data.Home);
  servo3.write(servo3_data.Home); 
}

#endif
