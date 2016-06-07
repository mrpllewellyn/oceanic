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
os.system("mjpg_streamer -i 'input_uvc.so -r 1280x720' -o 'output_http.so -w /srv/http/wwwwebcam' &")
time.sleep(2)
os.system("killall mjpg_streamer")

something_changed = 0

values = {
    'rudder': 100,
    'camera': 90,
    'motor': 0,
    'light': 0,
}

def sendSerial():
    global values
    ser.write(b'S0%dt99999\n' % int(values['rudder']))
    ser.write(b'S1%dt99999\n' % int(values['camera']))
    ser.write(b'M0%dt99999\n' % int(values['motor']))
    ser.write(b'M1%dt99999\n' % int(values['light']))

def background_thread():
    global something_changed
    count = 0
    while True:
        time.sleep(0.05)
        count += 1
        if something_changed == 1:
            sendSerial()
            something_changed = 0




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
    global something_changed
    values[message['who']] = message['data']
    emit('update value', message, broadcast=True)
    something_changed = 1

@socketio.on('connect', namespace='/oceanic')
def test_connect():
    emit('my response', {'data': 'Connecting', 'count': 0})


@socketio.on('disconnect', namespace='/oceanic')
def test_disconnect():
    print('Client disconnected', request.sid)

@socketio.on('webcam request', namespace='/oceanic')
def webcam_server():
    os.system("killall mjpg_streamer")
    os.system("mjpg_streamer -i 'input_uvc.so -r 1280x720' -o 'output_http.so -w /srv/http/wwwwebcam' &")

@socketio.on('reset request', namespace='/oceanic')
def reset_all():
    global values
    global something_changed
    values = {
        'rudder': 95,
        'camera': 59,
        'motor': 0,
        'light': 0,
    }
    something_changed = 1




if __name__ == '__main__':
    socketio.run(app, host='0.0.0.0')