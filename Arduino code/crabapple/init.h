#ifndef init_h
#define init_h

// include types & constants of Wiring core API
#include <Arduino.h>


void initfoo()
{
  load_conf();
  servoPtrs[0] = do_servo0; //initializes the arrays
  servoPtrs[1] = do_servo1;
  servoPtrs[2] = do_servo2;
  servoPtrs[3] = do_servo3;

  motorPtrs[0] = do_motor0; 
  motorPtrs[1] = do_motor1;

  lightPtrs[0] = do_light0; 

  buttonPtrs[0] = do_button0;
  buttonPtrs[1] = do_button1;
  
  servo_[0].attach(servodata[0].Pin);
  servo_[1].attach(servodata[1].Pin);
  servo_[2].attach(servodata[2].Pin);
  servo_[3].attach(servodata[3].Pin); 
  servo_[0].write(servodata[0].Home);
  servo_[1].write(servodata[1].Home);
  servo_[2].write(servodata[2].Home);
  servo_[3].write(servodata[3].Home); 
}

#endif
