#ifndef doCommands_h
#define doCommands_h

// include types & constants of Wiring core API
#include <Arduino.h>

//create command input struct
cmd cmd_input;
//create array of same structs for queuing/buffering commands
cmd cmd_q[CMD_BUFFER_SIZE];

//globals for command processing
byte cmd_counter = 1; //command constructer counter;
byte cmds_pending;
byte q_counter;
byte cmd_number;
String tmp_string;


void doButton(int index, int value, char action) {

  if (action == DO_CMD) {
    //nothing
  }

  else if (action == QUERY_CMD) {
    button_obj[index].state = !(digitalRead(button_obj[index].Pin));
    query_button(index);
  }

  else if (action == SETTIMEOUT_CMD) {
    //nothing 
  }

}

void doBuzzer(int index, int value, char action) {

  if (action == DO_CMD) {
    buzzer_obj[index].frequency = value;
    buzzer_obj[index].do_me = true;
  }

  else if (action == QUERY_CMD) {
    query_buzzer(index);
  }

  else if (action == SETTIMEOUT_CMD) {
    buzzer_obj[index].duration = value;
  }

}

void doProgram(int index, int value, char action) {
  
  if (action == DO_CMD) {
    if (index < num_programs){
      prgm_obj[index].lastMillis = millis();
      prgm_obj[index].do_me = true;
    }
  }

  else if (action == QUERY_CMD) {
    query_prog(index);
  }

  else if (action == SETTIMEOUT_CMD) {
    prgm_obj[index].Timeout = value;
  }
}

void doLight(int index, int value, char action) {

  if (action == DO_CMD) {
    light_obj[index].brightness = value;
    light_obj[index].lastMillis = millis();
    light_obj[index].do_me = true;
  }

  else if (action == QUERY_CMD) {
    query_light(index);
  }

  else if (action == SETTIMEOUT_CMD) {
    light_obj[index].Timeout = value;
  }

}

void doMotor(int index, int value, char action) {

  if (action == DO_CMD) {
    if (value < 0) {
      motor_obj[index].Direction = 0; //go backwards
      value = value * -1;
    }
    else {
      motor_obj[index].Direction = 1; //go forwards
    }
    //setMotorDirection(motor_obj[index].Direction, motor_obj[index].dirPin1, motor_obj[index].dirPin2);
    if (value <= motor_obj[index].Limit && value >= 0) {
      motor_obj[index].targetSpeed = value;
     // driveMotor(value, motor_obj[index].speedPin);
      motor_obj[index].lastMillis = millis();
      motor_obj[index].do_me = true;
    }
  }

  else if (action == QUERY_CMD) {
    query_motor(index);
  }

  else if (action == SETTIMEOUT_CMD) {
    motor_obj[index].Timeout = value;
  }

}

void doServo(int index, int value, char action) {

  if (action == DO_CMD) {
    if (value <= servo_obj[index].Max && value >= servo_obj[index].Min) {
      servo_obj[index].targetPos = value;
      //servo_[index].write(servo_obj[index].Pos);
      servo_obj[index].lastMillis = millis();
      servo_obj[index].do_me = true;
    }
  }

  else if (action == QUERY_CMD) {
    query_servo(index);
  }

  else if (action == SETTIMEOUT_CMD) {
    servo_obj[index].Timeout = value;
  }

}


/* commands are formatted like such: OBJTYPE OBJNUMBER ACTION VALUE
 *                                eg: 'S1:100' sets servo1 to position 100 degrees
 *                                    'M0t5000' sets motor0 timeout to 5000ms
 *                                    'L0?' queries the state of light0
 *                                    '?' queries everything
 * object type and action identifiers are set in conf.h
 */

void process_command() {
  if (cmd_q[cmd_number].obj_type == MOTOR_CMD) {
    int value = cmd_q[cmd_number].value;
    doMotor(cmd_q[cmd_number].obj_number, value, cmd_q[cmd_number].action_type);
  }

  else if (cmd_q[cmd_number].obj_type == SERVO_CMD) {
    int value = cmd_q[cmd_number].value;
    doServo(cmd_q[cmd_number].obj_number, value, cmd_q[cmd_number].action_type);
  }

  else if (cmd_q[cmd_number].obj_type == LIGHT_CMD) {
    int value = cmd_q[cmd_number].value;
    doLight(cmd_q[cmd_number].obj_number, value, cmd_q[cmd_number].action_type);
  }

  else if (cmd_q[cmd_number].obj_type == BUTTON_CMD) {
    int value = cmd_q[cmd_number].value;
    doButton(cmd_q[cmd_number].obj_number, value, cmd_q[cmd_number].action_type);
  }

  else if (cmd_q[cmd_number].obj_type == BUZZER_CMD) {
    int value = cmd_q[cmd_number].value;
    doBuzzer(cmd_q[cmd_number].obj_number, value, cmd_q[cmd_number].action_type);
  }

  else if (cmd_q[cmd_number].obj_type == PROG_CMD) {
    int value = cmd_q[cmd_number].value;
    doProgram(cmd_q[cmd_number].obj_number, value, cmd_q[cmd_number].action_type);
  }

  else {
    Serial.println(F("Command type not recognised"));
  }

  cmds_pending--;
  cmd_number++;
  if (cmd_number > (CMD_BUFFER_SIZE - 1)) {
    cmd_number = 0;
  }
}


void addCmdtoQ() { //add command to command Q
  cmd_q[q_counter] = cmd_input;
  q_counter++;
  if (q_counter > (CMD_BUFFER_SIZE - 1)) {
    q_counter = 0;
  }
  cmd_input = {0, 0, 0, 0};
  cmds_pending++;
}

//serial input is passed throught to this constructor byte by byte
//it makes a valid comand and passes it to the Q
void cmd_constructor(char inChar) { //construct commands from byte-by-byte input
  switch (cmd_counter) {
    case 1:
      cmd_input.obj_type = inChar;
      cmd_counter++;
      if (inChar == QUERY_CMD) {
        query_all();
        cmd_counter = 1;
      }
      if (inChar == END_OF_CMD) {
        cmd_counter = 1;
      }
      break;
    case 2:
      if (inChar == DO_CMD || inChar == QUERY_CMD || inChar == SETTIMEOUT_CMD) {
        cmd_input.obj_number = tmp_string.toInt();
        tmp_string = "";
        cmd_input.action_type = inChar;
        cmd_counter++;
      }
      else {
        tmp_string += inChar;
      }
      if (inChar == END_OF_CMD) {
        cmd_counter = 1;
        Serial.println(F("command error"));
      }
      break;
    case 3:
      if (inChar == END_OF_CMD) {
        cmd_input.value = tmp_string.toInt();
        tmp_string = "";
        cmd_counter = 1;
        addCmdtoQ();
      }
      else {
        tmp_string += inChar;
      }
      break;
  }
}

#endif
