#include <Servo.h>
#include "structs.h"
#include "conf.h"
#include "servoFunctions.h"
#include "motorFunctions.h"
#include "lightFunctions.h"
#include "buttonFunctions.h"
#include "programs.h"
#include "queryAll.h"
#include "comms.h"
#include "init.h"
#include "timeout.h"
#include "programTimer.h"

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
  check_timeouts();
  program_timer();
}



