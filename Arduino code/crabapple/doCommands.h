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


void doButton(int index, int value, char action) {

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

void doBuzzer(int index, int value, char action) {

  if (action == DO_CMD) {
    buzzer_obj[index].frequency = value;
    buzzer_obj[index].do_me = DO;
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
      prgm_obj[index].do_me = DO;
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
    light_obj[index].do_me = DO;
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

}

void doServo(int index, int value, char action) {

  if (action == DO_CMD) {
    if (value <= servo_obj[index].Max && value >= servo_obj[index].Min) {
      servo_obj[index].targetPos = value;
      //servo_[index].write(servo_obj[index].Pos);
      //servo_obj[index].do_me = true;
    }
    if (value == 0) {
      servo_obj[index].targetPos = 0;
    }
    else if (value < servo_obj[index].Min) {
      servo_obj[index].targetPos = servo_obj[index].Min;
    }
    else if (value > servo_obj[index].Max) {
      servo_obj[index].targetPos = servo_obj[index].Max;      
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

}


/* commands are formatted like such: OBJTYPE OBJNUMBER ACTION VALUE
 *                                eg: 'S1:100' sets servo1 to position 100 degrees
 *                                    'M0t5000' sets motor0 timeout to 5000ms
 *                                    'L0?' queries the state of light0
 *                                    '?' queries everything
 * object type and action identifiers are set in conf.h
 */

void process_command(int cmd_number) {
  if (cmd_q[cmd_number].obj_type == MOTOR_CMD) {
    if (motor_obj[cmd_q[cmd_number].obj_number].do_me == DONE) {
      int value = cmd_q[cmd_number].value;
      doMotor(cmd_q[cmd_number].obj_number, value, cmd_q[cmd_number].action_type);
      cmd_q[cmd_number].pending = false;
    }
  }

  else if (cmd_q[cmd_number].obj_type == SERVO_CMD) {
    if (servo_obj[cmd_q[cmd_number].obj_number].do_me == DONE) {
      int value = cmd_q[cmd_number].value;
      doServo(cmd_q[cmd_number].obj_number, value, cmd_q[cmd_number].action_type);
      cmd_q[cmd_number].pending = false;
    }
  }

  else if (cmd_q[cmd_number].obj_type == LIGHT_CMD) {
    if (light_obj[cmd_q[cmd_number].obj_number].do_me == DONE) {
      int value = cmd_q[cmd_number].value;
      doLight(cmd_q[cmd_number].obj_number, value, cmd_q[cmd_number].action_type);
      cmd_q[cmd_number].pending = false;
    }
  }

  else if (cmd_q[cmd_number].obj_type == BUTTON_CMD) {
    if (button_obj[cmd_q[cmd_number].obj_number].do_me == DONE) {
      int value = cmd_q[cmd_number].value;
      doButton(cmd_q[cmd_number].obj_number, value, cmd_q[cmd_number].action_type);
      cmd_q[cmd_number].pending = false;
    }
  }

  else if (cmd_q[cmd_number].obj_type == BUZZER_CMD) {
    if (buzzer_obj[cmd_q[cmd_number].obj_number].do_me == DONE) {
      int value = cmd_q[cmd_number].value;
      doBuzzer(cmd_q[cmd_number].obj_number, value, cmd_q[cmd_number].action_type);
      cmd_q[cmd_number].pending = false;
    }
  }

  else if (cmd_q[cmd_number].obj_type == PROG_CMD) {
    if (prgm_obj[cmd_q[cmd_number].obj_number].do_me == DONE) {
      int value = cmd_q[cmd_number].value;
      doProgram(cmd_q[cmd_number].obj_number, value, cmd_q[cmd_number].action_type);
      cmd_q[cmd_number].pending = false;
    }
  }

  else {
    Serial.println(F("Command type not recognised"));
  }

}


void addCmdtoQ() { //add command to command Q
  if (q_counter > (CMD_BUFFER_SIZE - 1)) {
    q_counter = 0;
  }  
  if (cmd_q[q_counter].pending == false) {
  cmd_q[q_counter] = cmd_input;
  q_counter++;
  }
  else if (cmd_q[q_counter].pending) {
    q_counter++;
    addCmdtoQ();
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
      if (inChar == END_OF_CMD) {
        char_counter = 1;
      }
      break;
    case 2:
      if (inChar == DO_CMD || inChar == QUERY_CMD || inChar == SETTIMEOUT_CMD || inChar == SETRATE_CMD) {
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
        cmd_input.pending = true;
        addCmdtoQ();
      }
      else {
        tmp_string += inChar;
      }
      break;
  }
}

#endif
