#ifndef doCommands_h
#define doCommands_h

// include types & constants of Wiring core API
#include <Arduino.h>

//create command input struct
cmd cmd_input;
//create array of same structs for queuing/buffering commands
cmd cmd_q[CMD_BUFFER_SIZE];
//globals for command processing
byte char_counter = 1; //command constructer counter;
byte q_counter;
String tmp_string;


void doButton(byte index, int value, char action) {

  if (action == DO_CMD) {
    //nothing
  }

  else if (action == QUERY_CMD) {
    query_button(index);
  }

  else if (action == SETTIMEOUT_CMD) {
    //nothing 
  }

}

void doBuzzer(byte index, int value, char action) {

  if (action == DO_CMD) {
    buzzer_obj[index].frequency = value;
    buzzer_obj[index].doMe = true;
  }

  else if (action == QUERY_CMD) {
    query_buzzer(index);
  }

  else if (action == SETTIMEOUT_CMD) {
    buzzer_obj[index].duration = value;
  }

}

void doProgram(byte index, int value, char action) {
  
  if (action == DO_CMD) {
    if (index < num_programs){
      prgm_obj[index].lastMillis = millis();
      prgm_obj[index].doMe = true;
    }
  }

  else if (action == QUERY_CMD) {
    query_prog(index);
  }

  else if (action == SETTIMEOUT_CMD) {
    prgm_obj[index].Timeout = value;
  }
}

void doLight(byte index, int value, char action) {

  if (action == DO_CMD && light_obj[index].isRunning == false) {
    Serial.println(F("doing light..."));
    light_obj[index].brightness = value;
    light_obj[index].doMe = true;
    light_obj[index].isRunning = true;
  }

  else if (action == QUERY_CMD) {
    query_light(index);
  }

  else if (action == SETTIMEOUT_CMD) {
    light_obj[index].Timeout = value;
  }

  else if (action == RESET_CMD) {
    light_obj[index].brightness = light_obj[index].default_brightness;    
    //now delete any commands for this object in the Q

    if (value != 1) {
      for (byte i = 0; i < CMD_BUFFER_SIZE; i++) {
        if (cmd_q[i].obj_type == LIGHT_CMD && cmd_q[i].obj_number == index) {
          cmd_q[i].obj_type = 0;
        }
      }      
    }

    light_obj[index].doMe = true;    
    light_obj[index].isRunning = false;
  }

}

void doMotor(byte index, int value, char action) {

  if (action == DO_CMD && motor_obj[index].isRunning == false) {
    if (value < 0) {
      motor_obj[index].Direction = 0; //go backwards
      value = value * -1;
    }
    else {
      motor_obj[index].Direction = 1; //go forwards
    }
    //setMotorDirection(motor_obj[index].Direction, motor_obj[index].dirPin1, motor_obj[index].dirPin2);
    if (value <= motor_obj[index].Max && value > motor_obj[index].Min) {
      motor_obj[index].targetSpeed = value;
     // driveMotor(value, motor_obj[index].speedPin);
     // motor_obj[index].do_me = true;
    }
    if (value == 0) {
      motor_obj[index].targetSpeed = 0;
    }
    else if (value < motor_obj[index].Min) {
      motor_obj[index].targetSpeed = motor_obj[index].Min;
    }
    else if (value > motor_obj[index].Max) {
      motor_obj[index].targetSpeed = motor_obj[index].Max;      
    }
  }

  else if (action == QUERY_CMD) {
    query_motor(index);
  }

  else if (action == SETTIMEOUT_CMD) {
    motor_obj[index].Timeout = value;
  }

  else if (action == SETRATE_CMD) {
    motor_obj[index].rate = value;
  }

  else if (action == RESET_CMD) {
    motor_obj[index].targetSpeed = 0;
    //now delete any commands for this object in the Q
    //but skip this step if value != 1
    if (value != 1) {
    for (byte i = 0; i < CMD_BUFFER_SIZE; i++) {
      if (cmd_q[i].obj_type == MOTOR_CMD && cmd_q[i].obj_number == index) {
        cmd_q[i].obj_type = 0;
      }
    }
    }
    motor_obj[index].doMe = true;
    motor_obj[index].isRunning = false;
  }

}

void doServo(byte index, int value, char action) {

  if (action == DO_CMD) {
    if (value <= servo_obj[index].Max && value >= servo_obj[index].Min) {
      servo_obj[index].targetPos = value;
      servo_obj[index].doMe = true;
      servo_obj[index].isRunning = true;
    }
    else if (value < servo_obj[index].Min) {
      servo_obj[index].targetPos = servo_obj[index].Min;
      servo_obj[index].doMe = true;
      servo_obj[index].isRunning = true;
    }
    else if (value > servo_obj[index].Max) {
      servo_obj[index].targetPos = servo_obj[index].Max;  
      servo_obj[index].doMe = true;
      servo_obj[index].isRunning = true;    
    }
  }

  else if (action == QUERY_CMD) {
    query_servo(index);
  }

  else if (action == SETTIMEOUT_CMD) {
    servo_obj[index].Timeout = value;
  }


  else if (action == SETRATE_CMD) {
    servo_obj[index].rate = value;
  }

  else if (action == RESET_CMD) {
    servo_obj[index].targetPos = servo_obj[index].Home;    
    //now delete any commands for this object in the Q

    if (value != 1) {
      for (byte i = 0; i < CMD_BUFFER_SIZE; i++) {
        if (cmd_q[i].obj_type == SERVO_CMD && cmd_q[i].obj_number == index) {
          cmd_q[i].obj_type = 0;
        }
      }      
    }

    servo_obj[index].doMe = true;    
    servo_obj[index].isRunning = false;
  }

}
//
void doReset() {
  Serial.println(F("reset all not implemented"));
//        doLight(i, 1, RESET_CMD);
//        doServo(i, 1, RESET_CMD);
//        doMotor(i, 1, RESET_CMD);
//        doBuzzer(i, 1, RESET_CMD);
}


/* commands are formatted like such: OBJTYPE OBJNUMBER ACTION VALUE
 *                                eg: 'S1:100' sets servo1 to position 100 degrees
 *                                    'M0t5000' sets motor0 timeout to 5000ms
 *                                    'L0?' queries the state of light0
 *                                    '?' queries everything
 * object type and action identifiers are set in conf.h
 */

void process_command(int cmd_number) {
  Serial.println(F("processing cmd..."));
  if (cmd_q[cmd_number].obj_type == MOTOR_CMD) {
      doMotor(cmd_q[cmd_number].obj_number, cmd_q[cmd_number].value, cmd_q[cmd_number].action_type);
      cmd_q[cmd_number].obj_type = 0;
  }

  else if (cmd_q[cmd_number].obj_type == SERVO_CMD) {
      if (servo_obj[cmd_q[cmd_number].obj_number].isRunning == true && cmd_q[cmd_number].action_type == DO_CMD) {
      //don't run command if it can't run yet        
      }
//      else if (servo_obj[cmd_q[cmd_number].obj_number].isRunning == true && cmd_q[cmd_number].action_type == SETTIMEOUT_CMD) {
//      //don't run command if it can't run yet        
//      }
//      else if (servo_obj[cmd_q[cmd_number].obj_number].isRunning == true && cmd_q[cmd_number].action_type == SETRATE_CMD) {
//      //don't run command if it can't run yet        
//      }
      else {
        cmd_q[cmd_number].obj_type = 0;
        doServo(cmd_q[cmd_number].obj_number, cmd_q[cmd_number].value, cmd_q[cmd_number].action_type);
      }
  }

  else if (cmd_q[cmd_number].obj_type == LIGHT_CMD) {
      if (light_obj[cmd_q[cmd_number].obj_number].isRunning == true && cmd_q[cmd_number].action_type == DO_CMD) {
      //don't run command if it can't run yet        
      }
//      else if (light_obj[cmd_q[cmd_number].obj_number].isRunning == true && cmd_q[cmd_number].action_type == SETTIMEOUT_CMD) {
//      //don't run command if it can't run yet        
//      }
//      else if (light_obj[cmd_q[cmd_number].obj_number].isRunning == true && cmd_q[cmd_number].action_type == SETRATE_CMD) {
//      //don't run command if it can't run yet        
//      }
      else {
        cmd_q[cmd_number].obj_type = 0;
        doLight(cmd_q[cmd_number].obj_number, cmd_q[cmd_number].value, cmd_q[cmd_number].action_type);
      }
  }

  else if (cmd_q[cmd_number].obj_type == BUTTON_CMD) {
      doButton(cmd_q[cmd_number].obj_number, cmd_q[cmd_number].value, cmd_q[cmd_number].action_type);
      cmd_q[cmd_number].obj_type = 0;
  }

  else if (cmd_q[cmd_number].obj_type == BUZZER_CMD) {
    if (buzzer_obj[cmd_q[cmd_number].obj_number].isRunning == false) {
      doBuzzer(cmd_q[cmd_number].obj_number, cmd_q[cmd_number].value, cmd_q[cmd_number].action_type);
      cmd_q[cmd_number].obj_type = 0;
      buzzer_obj[cmd_q[cmd_number].obj_number].isRunning = true;
    }
  }

  else if (cmd_q[cmd_number].obj_type == PROG_CMD) {
    if (prgm_obj[cmd_q[cmd_number].obj_number].isRunning == false) {
      doProgram(cmd_q[cmd_number].obj_number, cmd_q[cmd_number].value, cmd_q[cmd_number].action_type);
      cmd_q[cmd_number].obj_type = 0;
    }
  }

  else {
    Serial.println(F("Command type not recognised"));
    cmd_q[cmd_number].obj_type = 0;
  }

}


void addCmdtoQ() { //add command to command Q
  byte used_slots = 0;
  beginning:
  if (q_counter > (CMD_BUFFER_SIZE - 1)) {
    q_counter = 0;
  }  
  if (cmd_q[q_counter].obj_type == 0) { //if the current slot in the q is of type null then write command to this slot
  cmd_q[q_counter] = cmd_input;
  Serial.println(q_counter);
  Serial.println(F("added to Q"));
  q_counter++;
  }
  else if (used_slots = (CMD_BUFFER_SIZE - 1)) {
    Serial.println(F("command Q full!"));
  }
  else if (cmd_q[q_counter].obj_type != 0) { //else move to the next slot and try again
    q_counter++;
    used_slots++;
    goto beginning;
  }

}

//serial input is passed throught to this constructor byte by byte
//it makes a valid comand and passes it to the Q
void cmd_constructor(char inChar) { //construct commands from byte-by-byte input
  switch (char_counter) {
    case 1:
      cmd_input.obj_type = inChar;
      char_counter++;
      if (inChar == QUERY_CMD) {
        query_all();
        char_counter = 1;
      }
      if (inChar == RESET_CMD) {
        doReset();
        char_counter = 1;
      }
      if (inChar == END_OF_CMD) {
        char_counter = 1;
      }
      break;
    case 2:
      if (inChar == DO_CMD || inChar == QUERY_CMD || inChar == SETTIMEOUT_CMD || inChar == SETRATE_CMD || inChar == RESET_CMD) {
        cmd_input.obj_number = tmp_string.toInt();
        tmp_string = "";
        cmd_input.action_type = inChar;
        char_counter++;
      }
      else {
        tmp_string += inChar;
      }
      if (inChar == END_OF_CMD) {
        char_counter = 1;
        Serial.println(F("command error"));
      }
      break;
    case 3:
      if (inChar == END_OF_CMD) {
        cmd_input.value = tmp_string.toInt();
        tmp_string = "";
        char_counter = 1;
        Serial.println(F("command created"));
        addCmdtoQ();
      }
      else {
        tmp_string += inChar;
      }
      break;
  }
}

#endif
