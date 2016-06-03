#!/usr/bin/env python

# Set this variable to "threading", "eventlet" or "gevent" to test the
# different async modes, or leave it set to None for the application to choose
# the best option based on available packages.
async_mode = None

if async_mode is None:
    try:
        import eventlet
        async_mode = 'eventlet'
    except ImportError:
        pass

    if async_mode is None:
        try:
            from gevent import monkey
            async_mode = 'gevent'
        except ImportError:
            pass

    if async_mode is None:
        async_mode = 'threading'

    print('async_mode is ' + async_mode)

# monkey patching is necessary when using a background
# thread
if async_mode == 'eventlet':
    import eventlet
    eventlet.monkey_patch()
elif async_mode == 'gevent':
    from gevent import monkey
    monkey.patch_all()

import time, sys, tty, os, serial
from threading import Thread
from flask import Flask, render_template, session, request
from flask_socketio import SocketIO, emit, join_room, leave_room, \
    close_room, rooms, disconnect

app = Flask(__name__)
app.config['SECRET_KEY'] = 'secret!'
socketio = SocketIO(app, async_mode=async_mode)
thread = None

ser = serial.Serial('/dev/ttyACM0', 9600)
time.sleep(2)

values = {
    'rudder': 95,
    'camera': 59,
    'motor': 0,
    'light': 0,
    'reshorizontal': 640,
    'resvertical': 480,
    'fps': 5,
}

def sendSerial():
    global values
    ser.write(b'S0%dt99999\n' % int(values['rudder']))
    ser.write(b'S1%dt99999\n' % int(values['camera']))
    ser.write(b'M0%dt99999\n' % int(values['motor']))
    ser.write(b'M1%dt99999\n' % int(values['light']))

def background_thread():
    count = 0
    while True:
        time.sleep(0.1)
        count += 1
        sendSerial()




@app.route('/')
def index():
    global thread
    if thread is None:
        thread = Thread(target=background_thread)
        thread.daemon = True
        thread.start()
    return render_template('boat.html', **values)


@socketio.on('my event', namespace='/oceanic')
def message(message):
    session['receive_count'] = session.get('receive_count', 0) + 1
    emit('my response',
         {'data': message['data'], 'count': session['receive_count']})

@socketio.on('values changed', namespace='/oceanic')
def values_changed(message):
    values[message['who']] = message['data']
    emit('update value', message, broadcast=True)

@socketio.on('connect', namespace='/oceanic')
def test_connect():
    emit('my response', {'data': 'Connecting', 'count': 0})


@socketio.on('disconnect', namespace='/oceanic')
def test_disconnect():
    print('Client disconnected', request.sid)

@socketio.on('reset request', namespace='/oceanic')
def reset_all():
    global values
    values = {
        'rudder': 95,
        'camera': 59,
        'motor': 0,
        'light': 0,
        'reshorizontal': 640,
        'resvertical': 480,
        'fps': 5,
    }

if __name__ == '__main__':
    socketio.run(app, host='0.0.0.0')