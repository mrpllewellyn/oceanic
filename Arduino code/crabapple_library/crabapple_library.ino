#include <Servo.h> 
#include "structs.h" //defines data structures for each object type. commands are also stored in a struct.
#include "conf.h" //configures number of obects of each type and sets their properties
#include "servoFunctions.h" //servo related functions, so far read/write servo, timeout and query function 
#include "motorFunctions.h" //motor related functions, so far set speed, set direction, set timeout, and query
#include "lightFunctions.h" //motor related functions, so far set speed, set direction, set timeout, and query
#include "buttonFunctions.h" //button related function, so far read state and query 
#include "programs.h" //custom programs that can be called via commands
#include "queryAll.h" //function to query all objects of each type
#include "comms.h" //this is where the command constructor, command Q and command processing live
#include "init.h" //has code for attaching servos and defines custom programs, pin mode stuff can go here to
#include "timeout.h" // checks to see if somethis running needs to stop running
#include "programTimer.h" //timer for calling programs while their state property is true. state property is set by commands and switched off by timeout.h or another command

void setup()
{
  Serial.begin(9600); //we use serial for our comms
  initfoo(); //attach and set servos to home position, declare custom programs
  Serial.println("init complete");
}

void serialEvent() {
  while (Serial.available() && cmds_pending < CMD_BUFFER_SIZE) { //while serial is available and while command Q is not full
    // get the new byte:
    cmd_constructor((char)Serial.read()); //send each character of input to the command constructor. this creates valid commands than can be processed.
  }
}

void loop()
{
  if (cmds_pending > 0) { //if there is a job to do
    process_command(); // then do it
  }
  check_timeouts(); //does anything need to stop
  program_timer(); //does any program need to start
}



