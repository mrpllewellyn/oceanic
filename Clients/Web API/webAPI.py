import serial
import sys, tty, time, os, json

from flask import Flask
app = Flask(__name__)

ser = serial.Serial('/dev/ttyACM0', 9600)
time.sleep(2)

thrust = 0
rudderpos = 95
camerapos = 59
light = 0

def sendSerial():
    global thrust
    global rudderpos
    global camerapos
    global light

    ser.write(b'S0%dt99999\n' % rudderpos)
    ser.write(b'S1%dt99999\n' % camerapos)
    ser.write(b'M0%dt99999\n' % thrust)
    ser.write(b'M1%dt99999\n' % light)

@app.route('/')
def returnState():
    global thrust
    global rudderpos
    global camerapos
    global light
    return false

@app.route('/increaseSpeed')
def increaseSpeed():
    global thrust
    global rudderpos
    global camerapos
    global light
    thrust = thrust + 13
    sendSerial()

@app.route('/steerLeft')
def steerLeft():
    global thrust
    global rudderpos
    global camerapos
    global light
    rudderpos = rudderpos - 5
    sendSerial()

@app.route('/decreaseSpeed')
def decreaseSpeed():

    global thrust
    global rudderpos
    global camerapos
    global light
    thrust = thrust - 13
    sendSerial()

@app.route('/steerRight')
def steerRight(amonut):

    global thrust
    global rudderpos
    global camerapos
    global light
    rudderpos = rudderpos + 5
    sendSerial()

@app.route('/cameraLeft')
def cameraLeft():

    global thrust
    global rudderpos
    global camerapos
    global light
    camerapos  = camerapos - 5
    sendSerial()

@app.route('/cameraRight')
def cameraRight():

    global thrust
    global rudderpos
    global camerapos
    global light
    camerapos = camerapos + 5
    sendSerial()

@app.route('/lightDim')
def lightDim():

    global thrust
    global rudderpos
    global camerapos
    global light
    light = 128
    sendSerial()

@app.route('/lightOn')
def lightOn():
    global thrust
    global rudderpos
    global camerapos
    global light
    light = 255
    sendSerial()

@app.route('/lightOff')
def lightOff():

    global thrust
    global rudderpos
    global camerapos
    global light
    light = 0
    sendSerial()

@app.route('/reset')
def reset_all():

    global thrust
    global rudderpos
    global camerapos
    global light
    thrust = 0
    camerapos = 59
    rudderpos = 95
    light = 0
    sendSerial()

