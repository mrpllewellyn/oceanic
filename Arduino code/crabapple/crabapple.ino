#include <Servo.h>
Servo servo0,servo1,servo2,servo3;

#include "structs.h"
#include "conf.h"
#include "Query.h"
#include "functionPointers.h"
#include "servoFunctions.h"
#include "motorFunctions.h"
#include "lightFunctions.h"
#include "buttonFunctions.h"
#include "comms.h"
#include "init.h"
           
void setup()
{
  Serial.begin(9600);
  initfoo();
  Serial.println("init complete");

}

void serialEvent() {
  while (Serial.available() && cmds_pending < CMD_BUFFER_SIZE) {
    // get the new byte:
    cmd_constructor((char)Serial.read());
  }
  
}

 
void loop()
{
  if (cmds_pending > 0) {
    process_command();
  }
  delay(10);

}



