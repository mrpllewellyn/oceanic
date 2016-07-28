#ifndef init_h
#define init_h

// include types & constants of Wiring core API
#include <Arduino.h>


void initfoo()
{
  load_conf();

  for (int i = 0; i < num_servos; i++) {
    servo_[i].attach(servo_obj[i].Pin);
    servo_[i].write(servo_obj[i].Home);
  }

  programPtrs[0] = go_forward; //initializes the array
  programPtrs[1] = go_backward;
  programPtrs[2] = go_left;
  programPtrs[3] = go_right;
  programPtrs[4] = prgm_test;

  for (int i = 0; i < CMD_BUFFER_SIZE; i++) {
    cmd_q[i].obj_type = 0; // set all the commands to type = null so they don't trigger process_command needlessly
  }
}

#endif
