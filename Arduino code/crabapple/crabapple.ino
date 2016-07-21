#include <Servo.h> 
#include "structs.h" //defines data structures for each object type. commands are also stored in a struct.
#include "conf.h" //configures number of obects of each type and sets their properties
#include "query.h" //functions to query objects
#include "doCommands.h" //this is where the command constructor, command Q and command processing live
#include "customPrograms.h" //custom programs that can be called via commands
#include "watchdogs.h" //timer for calling programs while their state property is true. state property is set by commands and switched off by timeout.h or another command
#include "init.h" //has code for attaching servos and defines custom programs, pin mode stuff can go here to


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
  if (cmds_pending > 0) { //if there is a command to do
    process_command(); // then action it
  }
  watchdogs();
}



