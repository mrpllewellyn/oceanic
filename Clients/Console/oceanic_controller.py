#console controller for oceanic rc boat

import serial
import sys, tty, termios, time, os

ser = serial.Serial('/dev/ttyACM0', 9600)
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

def sendSerial(rudderpos, camerapos, thrust, light):

    ser.write(b'S0%dt99999\n' % rudderpos)
    ser.write(b'S1%dt99999\n' % camerapos)
    ser.write(b'M0%dt99999\n' % thrust)
    ser.write(b'M1%dt99999\n' % light)

# Instructions for when the user has an interface
print("w/s: forward/backwards")
print("a/d: steering")
print("q/e: camera pan")
print("=/-: light")
print("x: reset")
print("z: quit")
thrust = 0
rudderpos = 95
camerapos = 59
light = 0
while True:

    char = getch()
    if(char == "z"):
        print("quit")
        break


    if(char == "w"):
        thrust = thrust + 13

    if(char == "a"):
        rudderpos = rudderpos - 5

    if(char == "s"):
        thrust = thrust - 13

    if(char == "d"):
        rudderpos = rudderpos + 5

    if(char == "q"):
        camerapos  = camerapos - 5

    if(char == "e"):
        camerapos = camerapos + 5

    if(char == "="):
        light = light + 15
    if(char == "-"):
        light = light - 15


    if(char == "x"):
        thrust = 0
        camerapos = 59
        rudderpos = 95
        light = 0
    char = ""

    sendSerial(rudderpos, camerapos, thrust, light)
    os.system('clear')
    print('Thrust (w/s): %d' % thrust)
    print('Rudder (a/d): %d' % rudderpos)
    print('Camera (q/e): %d' % camerapos)
    print('Light  (=/-): %d' % light)
    print('Reset(x)/Quit(z)')
