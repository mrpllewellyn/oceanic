#console controller for two degrees of freedom studiono arm

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

def sendSerial(servo0, servo1):

    ser.write(b'S0%dt99999\n' % servo0)
    ser.write(b'S1%dt99999\n' % servo1)


# Instructions for when the user has an interface
print("w/s: forward/backwards")
print("a/d: left/back")
print("x: reset")
print("z: quit")
servo0 = 90
servo1 = 90

while True:

    char = getch()
    if(char == "z"):
        print("quit")
        break


    if(char == "w"):
        servo1 = servo1 + 5

    if(char == "a"):
        servo0 = servo0 - 5

    if(char == "s"):
        servo1 = servo1 - 5

    if(char == "d"):
        servo0 = servo0 + 5




    if(char == "x"):
        servo0 = 90
        servo1 = 90

    char = ""

    sendSerial(servo0, servo1)
    os.system('clear')
    print('Thrust (w/s): %d' % servo1)
    print('Rudder (a/d): %d' % servo0)
    print('Reset(x)/Quit(z)')
