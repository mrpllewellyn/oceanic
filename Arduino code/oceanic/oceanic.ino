// Arduino code for Atmega 2560 with a LinkSprite Motor Shield
// Code to control motors and servos on a modified RC boat
// Receives commands over serial and sets the motor speed/direction and servo positions


#include <Servo.h>

// generate servo objects
Servo servo_0,servo_1;

// Let's define some stuff!..

const int default_timeout = 1000; // fallback timeout if not specified, in ms

// Rudder servo
int servo_0_pos = 0; //define variable used for setting servo position
const int servo_0_home = 100; // sets the default centre/"home" position for the servo
const int servo_0_softmin = 42; // sets the minimum position that the rudder can turn to, in degrees
const int servo_0_softmax = 142; // sets the maximum position that the rudder can turn to, in degrees
const String servo_0_name = "rudder";
const String servo_0_desc = "Servo controlled rudder";
int servo_0_timeout = 1000; //sets initial timeout in ms for servo_0
unsigned long servo_0_tsl;
boolean servo_0_active = false; //let's us know if a command is being run on servo_0

// Camera servo
int servo_1_pos = 0; //define variable used for setting servo position
const int servo_1_home = 90; // sets the default centre/"home" position for the servo
const int servo_1_softmin = 0; // sets the minimum position that the camera can turn to, in degrees
const int servo_1_softmax = 180; // sets the maximum position that the camera can turn to, in degrees
const String servo_1_name = "camera";
const String servo_1_desc = "Servo to control camera on horizontal plane";
int servo_1_timeout = 1000; //sets initial timeout in ms for servo_1
unsigned long servo_1_tsl;
boolean servo_1_active = false; //let's us know if a command is being run on servo_1

// Define stuff for motor controller
// channel A - connect to DC motor driving boat prop
const String motor_0_name = "prop";
const String motor_0_desc = "12V DC Motor coupled to prop shaft";
int motor_0_direction_pin1 = 8;
int motor_0_direction_pin2 = 11;
int motor_0_speed_pin = 9;
int motor_0_speed = 0;

//channel B - no motor connected
const String motor_1_name = "nc";
const String motor_1_desc = "Motor controller channel B - nothing connected";
int motor_1_direction_pin1 = 12;
int motor_1_direction_pin2 = 13;
int motor_1_speed_pin = 10;
int motor_1_speed = 0;


int motor_0_timeout = 1000; // sets initial timeout in ms for motor_0
unsigned long motor_0_tsl;
boolean motor_0_active = false; //let's us know if a command is being run on motor_0
int motor_1_timeout = 1000; // sets initial timeout in ms for motor_1
unsigned long motor_1_tsl;
boolean motor_1_active = false; //let's us know if a command is being run on motor_1


//Serial input
String serial_input = "";
boolean serial_received = false; // informs void_loop that there is a command to process
String current_cmd = "";

//random variables used for processing command strings
int timeout = 0;
String objnumber;
int pos = 0;



void setup() {
  
  // Init motor controller pins
  //motor controller channel A
  pinMode(motor_0_direction_pin1, OUTPUT);
  pinMode(motor_0_direction_pin2, OUTPUT);
  pinMode(motor_0_speed_pin, OUTPUT);  
  //motor controller channel B
  pinMode(motor_1_direction_pin1, OUTPUT);
  pinMode(motor_1_direction_pin2, OUTPUT);
  pinMode(motor_1_speed_pin, OUTPUT);
  
  //Init servos
  servo_0.attach(6); //Rudder servo connected to pin 3
  servo_1.attach(5); //Camera servo connected to pin 5
  servo_1.write(servo_1_home);
  servo_0.write(servo_0_home);
  //Init serial connection
  Serial.begin(9600);
}


void loop() {
  
  // check if we should start doing anything
  if (serial_received) {
    serial_received = false;
    process_command();
  }

  //check if we should stop doing anything
  check_timeouts();

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

  //motor 1
  if (motor_0_active){
    if (millis() - motor_0_tsl >= motor_0_timeout){  
      motor_0_brake();
      motor_0_active = false;
    }
  }

  //motor 2
  if (motor_1_active){
    if (millis() - motor_1_tsl >= motor_1_timeout){  
      motor_1_brake();
      motor_1_active = false;
    }
  }
}

void process_command() {

  // COMMANDS
  // Commands are structured in the following way:
  // 1st char: command type (S)ervo/(M)otor/(Q)uery
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
      if (current_cmd.charAt(0) == '+'){ // if the servo position is prefixed with '+' or '-' then is will move relative to the centre position ("home") of the servo
      pos = servo_0_home + (current_cmd.substring(1)).toInt();
      servo_0_pos = pos;
      }
      else if (current_cmd.charAt(0) == '-'){
      pos = servo_0_home - (current_cmd.substring(1)).toInt();
      servo_0_pos = pos;
      }
      else { // otherwise the servo position is absolute, set in degrees
      pos = current_cmd.toInt();
      servo_0_pos = pos;
      }
      servo_0_timeout = timeout;
      servo_0_set();
      break;
    case 1:
      if (current_cmd.charAt(0) == '+'){
      pos = servo_1_home + (current_cmd.substring(1)).toInt();
      servo_1_pos = pos;
      }
      else if (current_cmd.charAt(0) == '-'){
      pos = servo_1_home - (current_cmd.substring(1)).toInt();
      servo_1_pos = pos;
      }
      else {
      pos = current_cmd.toInt();
      servo_1_pos = pos;
      }
      servo_1_timeout = timeout;
      servo_1_set();
      break;
    default: 
      Serial.println("unrecognised servo number\n");
      break;
    }

  }
 
  else if (cmdtype == 'Q'){
    
  }
  else {
  Serial.println("Command type not recognised\n");    
  }
}

void motor_0_set() {
  if (motor_0_speed < 0) {
    digitalWrite(motor_0_direction_pin1,HIGH);//set direction anticlockwise
    digitalWrite(motor_0_direction_pin2,LOW);
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

void motor_1_set() {
  if (motor_1_speed < 0) {
    digitalWrite(motor_1_direction_pin1,LOW);//set direction clockwise
    digitalWrite(motor_1_direction_pin2,HIGH);//motor_1 is connected to a LED array so we don't want to go backwards!
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

void motor_0_brake() {
  //code to stop motor_0
  //slow and stop motor
  while (motor_0_speed > 20){
    motor_0_speed = motor_0_speed - (motor_0_speed/10);
    //write motor speed
    analogWrite(motor_0_speed_pin,motor_0_speed);
    delay(15);
  }
  if (motor_0_speed <= 20){
    motor_0_speed = 0;
     digitalWrite(motor_0_speed,LOW);
     digitalWrite(motor_0_speed,LOW);
        //set motor speed
     analogWrite(motor_0_speed_pin,motor_0_speed);
    
  }
}

void motor_1_brake() {
  //code to stop motor_1 (LED LIGHT)
  analogWrite(motor_1_speed_pin,0);
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
