# console controller for studuino based 4 wheeled robot
# two wheels are powered, all 4 can be rotated 180 degrees

import serial
import sys, tty, termios, time, os

ser = serial.Serial('/dev/ttyUSB0', 9600)
time.sleep(2)

# The getch method can determine which key has been pressed
# by the user on the keyboard by accessing the system files
# It will then return the pressed key as a variable
def getch():
    fd = sys.stdin.fileno()
    old_settings = termios.tcgetattr(fd)
    try:
        tty.setraw(sys.stdin.fileno())
        ch = sys.stdin.read(1)
    finally:
        termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
    return ch

def sendSerial(motor0, motor1, servo0, servo1, servo2, servo3, light0):

    ser.write(b'M0:%d\n' % motor0)
    ser.write(b'M1:%d\n' % motor1)
    ser.write(b'S0:%d\n' % servo0)
    ser.write(b'S1:%d\n' % servo1)
    ser.write(b'S2:%d\n' % servo2)
    ser.write(b'S3:%d\n' % servo3)
    ser.write(b'L0:%d\n' % light0)
    
def settimeout(motor0_timeout, motor1_timeout, servo0_timeout, servo1_timeout, servo2_timeout, servo3_timeout, light0_timeout):
	
    ser.write(b'M0t%d\n' % motor0_timeout)
    ser.write(b'M1t%d\n' % motor1_timeout)
    ser.write(b'S0t%d\n' % servo0_timeout)
    ser.write(b'S1t%d\n' % servo1_timeout)
    ser.write(b'S2t%d\n' % servo2_timeout)
    ser.write(b'S3t%d\n' % servo3_timeout)
    ser.write(b'L0t%d\n' % light0_timeout)

# Instructions for when the user has an interface
print("w/s: forward/backwards")
print("a/d: steering")
print("q/e: camera pan")
print("l: light")
print("x: reset")
print("z: quit")
motor0 = 0
motor1 = 0
servo0 = 90
servo1 = 90
servo2 = 90
servo3 = 90
light0 = 0
motor0_timeout = 500
motor1_timeout = 500
servo0_timeout = 1000
servo1_timeout = 1000
servo2_timeout = 1000
servo3_timeout = 1000
light0_timeout = 100

while True:

    settimeout(motor0_timeout, motor1_timeout, servo0_timeout, servo1_timeout, servo2_timeout, servo3_timeout, light0_timeout)
    sendSerial(motor0, motor1, servo0, servo1, servo2, servo3, light0)
    char = getch()
    if(char == "z"):
        print("quit")
        break


    if(char == "w"):
        motor0 = 255
        motor1 = 255
        servo0 = 90
        servo1 = 90
        servo2 = 90
        servo3 = 90
        
    if(char == "a"):
        motor0 = 255
        motor1 = 255
        servo0 = 0
        servo1 = 0
        servo2 = 0
        servo3 = 0
        

    if(char == "s"):
        motor0 = -255
        motor1 = -255
        servo0 = 90
        servo1 = 90
        servo2 = 90
        servo3 = 90
        
    if(char == "d"):
        motor0 = 255
        motor1 = 255
        servo0 = 180
        servo1 = 180
        servo2 = 180
        servo3 = 180
        
    if(char == "q"):
        motor0 = 255
        motor1 = -255
        servo0 = 90
        servo1 = 0
        servo2 = 0
        servo3 = 90
        
    if(char == "e"):
        motor0 = -255
        motor1 = 255
        servo0 = 90
        servo1 = 180
        servo2 = 180
        servo3 = 90
        
    if(char == "x"):
       motor0 = 0
       motor1 = 0
       servo0 = 90
       servo1 = 90
       servo2 = 90
       servo3 = 90
       
    if(char == "l"):
       light0 = 255
    char = ""
    
