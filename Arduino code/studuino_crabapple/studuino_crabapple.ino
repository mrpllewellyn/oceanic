// Arduino code to control 4 servos and 2 DC motor
// Receives commands over serial

#include <MsTimer2.h>
#include <Servo.h>
#include "constants.h"
#include "pins.h"

// generate servo objects
Servo servo_0,servo_1,servo_2,servo_3;

// Let's define some stuff!..

const int default_timeout = 1000; // fallback timeout if not specified, in ms

//  servo 0
int servo_0_pos = 0; //define variable used for setting servo position
int servo_0_timeout = 1000; //sets initial timeout in ms for servo_0
unsigned long servo_0_tsl;
boolean servo_0_active = false; //let's us know if a command is being run on servo_0

//  servo 1
int servo_1_pos = 0; //define variable used for setting servo position
int servo_1_timeout = 1000; //sets initial timeout in ms for servo_1
unsigned long servo_1_tsl;
boolean servo_1_active = false; //let's us know if a command is being run on servo_1

//  servo 2
int servo_2_pos = 0; //define variable used for setting servo position
int servo_2_timeout = 1000; //sets initial timeout in ms for servo_2
unsigned long servo_2_tsl;
boolean servo_2_active = false; //let's us know if a command is being run on servo_2

//  servo 3
int servo_3_pos = 0; //define variable used for setting servo position
int servo_3_timeout = 1000; //sets initial timeout in ms for servo_3
unsigned long servo_3_tsl;
boolean servo_3_active = false; //let's us know if a command is being run on servo_3

// motor 0
int motor_0_speed = 0;
int motor_0_timeout = 1000; // sets initial timeout in ms for motor_0
unsigned long motor_0_tsl;
boolean motor_0_active = false; //let's us know if a command is being run on motor_0
boolean motor_0_direction_lock = false;

// motor 1
int motor_1_timeout = 1000; // sets in1itial timeout in ms for motor_1
unsigned long motor_1_tsl;
boolean motor_1_active = false; //let's us know if a command is being run on motor_1
boolean motor_1_direction_lock = false;
int motor_1_speed = 0;

int bumperLeftstate = 0;
int bumperRightstate = 0;

//Serial input
String serial_input = "";
boolean serial_received = false; // informs void_loop that there is a command to process
String current_cmd = "";

boolean inhibit_input = false;

//random variables used for processing command strings
int timeout = 0;
String objnumber;
int pos = 0;



void setup() {
    
  //Init servos
  servo_0.attach(9);
  servo_1.attach(10);
  servo_2.attach(11);
  servo_3.attach(12);
  servo_1.write(servo_1_home);
  servo_0.write(servo_0_home);
  servo_2.write(servo_2_home);
  servo_3.write(servo_3_home);

  //Init serial connection
  Serial.begin(9600);

  //check state of the bumper switches every 100ms
  MsTimer2::set(100, safety_checks); // perform safety checks every 100ms period, can't use hardware interupts because the pins 2 and 3 are used elsewhere
  MsTimer2::start();
}


void loop() {
  
  // check if we should start doing anything
  if (serial_received) {
    serial_received = false;
    if (inhibit_input == false) {
      process_command();
    }
  }

  //check if we should stop doing anything
  check_timeouts();
}

void serialEvent() {
  // reads bytes from serial until a newline is detected
  // serial_received then become true so the main program knows there is a command to process
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    serial_input += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      serial_received = true;
    }
  }
  
}

void process_command() {

  // COMMANDS
  // Commands are structured in the following way:
  // 1st char: command type (S)ervo/(M)otor/(?)Query
  // 2nd char: object number, starts at 0. e.g. S0 for servo_0
  // 3rd char+ : value to be set. Either motor (speed/direction), servo position or switch state.
  // switch state is 1 or 0
  // servo position should be between 0-360, and is limited by softmin and softmax constants anyway. Servo will go as close to given value as it can within these constraints.
  // motor speed can be any value, but will max out at 255 regardless. Higher values are harmless but won't make anything faster!
  // motor direction is determined by polarity of value i.e. -255 is anticlockwise and 225 is clockwise.
  // a timeout option can be appended to the command, but is optional
  // this is achieved by adding the letter 't' followed by the desired timeout (in ms) to the end of the command.
  // timeout will only effect the motor/servo specified in the command
  // each command should end with '\n' (newline) 
  // 
  // examples:
  // S090t1000\n - set servo_0 to 90 degrees and timeout in 1 second
  // M1-255t2000\n - set motor_1 to full speed in an anticlockwise direction. Timeout in 2 seconds.
  // S1+30\n - turn servo_1 30 degrees clockwise. No timeout is specified so will fallback to deault_timeout
  // M0125t500\n - run motor clockwise at half speed. Runs for 500ms.
  
  current_cmd = serial_input;
  serial_input = "";
  char cmdtype = current_cmd.charAt(0); // read the first letter of the command, this indicates the command type - M/motor S/servo X/switch Q/query

  if (cmdtype == 'M'){
    
    objnumber = current_cmd.charAt(1); //get motor number
    int trimpos = current_cmd.indexOf('t');    //check if timeout has been spec
    if (trimpos != -1){
      timeout = (current_cmd.substring(trimpos + 1)).toInt();
      current_cmd = current_cmd.substring(2,trimpos);
    }
    else {
      timeout = default_timeout;
      current_cmd = current_cmd.substring(2);
      current_cmd = current_cmd.substring(0,(current_cmd.length() - 1));
    }
    
    int value = objnumber.toInt();
    switch (value) {
    case 0:
      motor_0_speed = current_cmd.toInt();
      motor_0_timeout = timeout;
      motor_0_set();
      break;
    case 1:
      motor_1_speed = current_cmd.toInt();
      motor_1_timeout = timeout;
      motor_1_set();
      break;
    default: 
      Serial.println("unrecognised motor number\n");
      break;
    }
  }
  else if (cmdtype == 'S'){
    
    objnumber = current_cmd.charAt(1); //get servo number
    int trimpos = current_cmd.indexOf('t');
    if (trimpos != -1){
      timeout = (current_cmd.substring(trimpos + 1)).toInt();
      current_cmd = current_cmd.substring(2,trimpos);
    }
    else {
      timeout = default_timeout;
      current_cmd = current_cmd.substring(2);
      current_cmd = current_cmd.substring(0,(current_cmd.length() - 1));
    }
    int value = objnumber.toInt();
    switch (value) {
    case 0:
      pos = current_cmd.toInt();
      servo_0_pos = pos;
      servo_0_timeout = timeout;
      servo_0_set();
      break;
    case 1:
      pos = current_cmd.toInt();
      servo_1_pos = pos;
      servo_1_timeout = timeout;
      servo_1_set();
      break;
    case 2:
      pos = current_cmd.toInt();
      servo_2_pos = pos;
      servo_2_timeout = timeout;
      servo_2_set();
      break;
    case 3:
      pos = current_cmd.toInt();
      servo_3_pos = pos;
      servo_3_timeout = timeout;
      servo_3_set();
      break;
    default: 
      Serial.println("unrecognised servo number\n");
      break;
    }

  }
 
  else if (cmdtype == '?'){
    
  }
  else {
  Serial.println("Command type not recognised\n");    
  }
}


void motor_0_brake() {
    motor_0_speed = 0;
     digitalWrite(motor_0_speed,LOW);
        //set motor speed
     analogWrite(motor_0_speed_pin,motor_0_speed);
}

void motor_0_set() {
  if (motor_0_speed < 0) {
    if (motor_0_direction_lock == false) {
      digitalWrite(motor_0_direction_pin1,HIGH);//set direction anticlockwise
      digitalWrite(motor_0_direction_pin2,LOW);
    }
    else {
      digitalWrite(motor_0_direction_pin1,LOW);//set direction clockwise
      digitalWrite(motor_0_direction_pin2,HIGH);
    }
    motor_0_speed = motor_0_speed * -1; // don't be so negative!
  }
  else { 
      digitalWrite(motor_0_direction_pin1,LOW);//set direction clockwise
      digitalWrite(motor_0_direction_pin2,HIGH);
  }

  //run motor at given speed
  analogWrite(motor_0_speed_pin, motor_0_speed);  
  motor_0_tsl = millis();
  motor_0_active = true;
}

void motor_1_brake() {
  //code to stop motor_1
    motor_1_speed = 0;
     digitalWrite(motor_1_speed,LOW);
        //set motor speed
     analogWrite(motor_1_speed_pin,motor_1_speed);
}

void motor_1_set() {
  if (motor_1_speed < 0) {
    if (motor_1_direction_lock == false) {
      digitalWrite(motor_1_direction_pin1,HIGH);//set direction anticlockwise
      digitalWrite(motor_1_direction_pin2,LOW);
    }
    else {
      digitalWrite(motor_1_direction_pin1,LOW);//set direction clockwise
      digitalWrite(motor_1_direction_pin2,HIGH);
    }
    motor_1_speed = motor_1_speed * -1; // don't be so negative!
  }
  else { 
      digitalWrite(motor_1_direction_pin1,LOW);//set direction clockwise
      digitalWrite(motor_1_direction_pin2,HIGH);
  }


  //run motor at given speed
  analogWrite(motor_1_speed_pin, motor_1_speed);  
  motor_1_tsl = millis();
  motor_1_active = true;
}

void servo_0_set() { // sets the servo to position
  if (servo_0_pos < servo_0_softmin){ // servo position is constrained by softmin and softmax
    servo_0.write(servo_0_softmin);
  }
  else if (servo_0_pos > servo_0_softmax){
    servo_0.write(servo_0_softmax);
  }
  else {
    servo_0.write(servo_0_pos);
  }
  servo_0_tsl = millis();
  servo_0_active = true;
}

void servo_1_set() { // sets the servo to position
  if (servo_1_pos < servo_1_softmin){// servo position is constrained by softmin and softmax
    servo_1.write(servo_1_softmin);
  }
  else if (servo_1_pos > servo_1_softmax){
    servo_1.write(servo_1_softmax);
  }
  else {
    servo_1.write(servo_1_pos);
  }
  servo_1_tsl = millis();
  servo_1_active = true;
}

void servo_2_set() { // sets the servo to position
  if (servo_2_pos < servo_2_softmin){ // servo position is constrained by softmin and softmax
    servo_2.write(servo_2_softmin);
  }
  else if (servo_2_pos > servo_2_softmax){
    servo_2.write(servo_2_softmax);
  }
  else {
    servo_2.write(servo_2_pos);
  }
  servo_2_tsl = millis();
  servo_2_active = true;
}

void servo_3_set() { // sets the servo to position
  if (servo_3_pos < servo_3_softmin){// servo position is constrained by softmin and softmax
    servo_3.write(servo_3_softmin);
  }
  else if (servo_3_pos > servo_3_softmax){
    servo_3.write(servo_3_softmax);
  }
  else {
    servo_3.write(servo_3_pos);
  }
  servo_3_tsl = millis();
  servo_3_active = true;
}

void check_timeouts() {
    // monitor timeouts and reset motors/servos accordingly
  
  //servo 1
  if (servo_0_active){
    if (millis() - servo_0_tsl >= servo_0_timeout){  
      servo_0.write(servo_0_home);
      servo_0_active = false;
    }
  }

  //servo 2
  if (servo_1_active){
    if (millis() - servo_1_tsl >= servo_1_timeout){  
      servo_1.write(servo_1_home);
      servo_1_active = false;
    }
  }

  //servo 3
  if (servo_2_active){
    if (millis() - servo_2_tsl >= servo_2_timeout){  
      servo_2.write(servo_2_home);
      servo_2_active = false;
    }
  }

  //servo 4
  if (servo_3_active){
    if (millis() - servo_3_tsl >= servo_3_timeout){  
      servo_3.write(servo_3_home);
      servo_3_active = false;
    }
  }

  //motor 0
  if (motor_0_active){
    if (millis() - motor_0_tsl >= motor_0_timeout){  
      motor_0_brake();
      motor_0_active = false;
    }
  }
  //motor 1
  if (motor_1_active){
    if (millis() - motor_1_tsl >= motor_1_timeout){  
      motor_1_brake();
      motor_1_active = false;
    }
  }


}

void process_query() {
  
}

void safety_checks() {
  // if bumpers = 1 then prevent motor driving forward
  // motor_0_direction_lock = true;
  // motor_1_direction_lock = true;
  //      digitalWrite(motor_0_direction_pin1,HIGH);//set direction anticlockwise
  //    digitalWrite(motor_0_direction_pin2,LOW);
  // else
  // motor_0_direction_lock = false;
  // motor_1_direction_lock = false;
  bumperLeftstate = analogRead(bumperLeft);
  bumperRightstate = analogRead(bumperRight);
  if (bumperRightstate == 0) {
    motor_0_direction_lock = 1;
    motor_1_direction_lock = 1;
  }
  else if (bumperLeftstate == 0) {
    motor_0_direction_lock = 1;
    motor_1_direction_lock = 1;
  }
  else {
    motor_0_direction_lock = 0;
    motor_1_direction_lock = 0;
  }
    
}




