#ifndef comms_h
#define comms_h

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


void process_command() {
  
  if (cmd_q[cmd_number].obj_type == MOTOR_CMD){
    int value = cmd_q[cmd_number].value;
    callMotor(cmd_q[cmd_number].obj_number, value, cmd_q[cmd_number].action_type);
 } 
 
  else if (cmd_q[cmd_number].obj_type == SERVO_CMD){
    int value = cmd_q[cmd_number].value;
    callServo(cmd_q[cmd_number].obj_number, value, cmd_q[cmd_number].action_type);
  }

  else if (cmd_q[cmd_number].obj_type == LIGHT_CMD){
    int value = cmd_q[cmd_number].value;
    callLight(cmd_q[cmd_number].obj_number, value, cmd_q[cmd_number].action_type);
  }

  else if (cmd_q[cmd_number].obj_type == BUTTON_CMD){
    int value = cmd_q[cmd_number].value;
    callButton(cmd_q[cmd_number].obj_number, value, cmd_q[cmd_number].action_type);
  }
  
  else {
  Serial.println(F("Command type not recognised"));    
  }
  
  cmds_pending--;
  cmd_number++;
  if (cmd_number > (CMD_BUFFER_SIZE - 1)){
    cmd_number = 0;
  }

}

void query_all() {
  for (int i = 0; i < num_servos; i++){
    Serial.print(F("servo:"));
    Serial.println(i);
    callServo(i, 0, QUERY_CMD);
    Serial.println();
  }
  for (int i = 0; i < num_motors; i++){
    Serial.print(F("motor:"));
    Serial.println(i);
    callMotor(i, 0, QUERY_CMD);
    Serial.println();
  }
  for (int i = 0; i < num_lights; i++){
    Serial.print(F("light:"));
    Serial.println(i);
    callLight(i, 0, QUERY_CMD);
    Serial.println();
  }
  for (int i = 0; i < num_buttons; i++){
    Serial.print(F("button:"));
    Serial.println(i);
    callButton(i, 0, QUERY_CMD);
    Serial.println();
  }
}

void cmd_queue() { //add command to command Q
  cmd_q[q_counter] = cmd_input;
  q_counter++;
  if (q_counter > (CMD_BUFFER_SIZE - 1)){
    q_counter = 0;
  }
  cmd_input = {0,0,0,0};
  cmds_pending++;
}

void cmd_constructor(char inChar) { //construct commands from byte-by-byte input
  switch (cmd_counter) {
  case 1:
    cmd_input.obj_type = inChar;
    cmd_counter++;
    if (inChar == QUERY_CMD){
      query_all();
      cmd_counter = 1;
    }
    if (inChar == END_OF_CMD){cmd_counter = 1;}
    break;
  case 2:
    if (inChar == DO_CMD || inChar == QUERY_CMD || inChar == SETTIMEOUT_CMD){
      cmd_input.obj_number = tmp_string.toInt();
      tmp_string = "";
      cmd_input.action_type = inChar;
      cmd_counter++;
    }
    else {
      tmp_string += inChar;
    }
    if (inChar == END_OF_CMD){cmd_counter = 1; Serial.println(F("command error"));}
    break;
  case 3:
    if (inChar == END_OF_CMD){
      cmd_input.value = tmp_string.toInt();
      tmp_string = "";
      cmd_counter = 1;
      cmd_queue();
    }
    else {
      tmp_string += inChar;
    }
    break;
  }
}





#endif
