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

ser = serial.Serial('/dev/ttyUSB0', 9600)
#os.system("mjpg_streamer -i 'input_uvc.so -r 1280x720 -f 5' -o 'output_http.so -w /srv/http/wwwwebcam' &")
time.sleep(2)
#os.system("killall mjpg_streamer")

something_changed = 0

values = {
    'servo0': 90,
    'servo1': 90,
    'servo2': 90,
    'servo3': 90,
    'servo4': 90,
    'servo5': 90,
    'motor0': 0,
}

def sendSerial():
    global values
    ser.write(b'S0%dt99999\n' % int(values['servo0']))
    ser.write(b'S1%dt99999\n' % int(values['servo1']))
    ser.write(b'S2%dt99999\n' % int(values['servo2']))
    ser.write(b'S3%dt99999\n' % int(values['servo3']))
    ser.write(b'S4%dt99999\n' % int(values['servo4']))
    ser.write(b'S5%dt99999\n' % int(values['servo5']))
    ser.write(b'M0%dt99999\n' % int(values['motor0']))
    
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
    return render_template('studuino.html', **values)


@socketio.on('my event', namespace='/seasquirt')
def message(message):
    session['receive_count'] = session.get('receive_count', 0) + 1
    emit('my response',
         {'data': message['data'], 'count': session['receive_count']})

@socketio.on('values changed', namespace='/seasquirt')
def values_changed(message):
    global something_changed
    values[message['who']] = message['data']
    emit('update value', message, broadcast=True)
    something_changed = 1

@socketio.on('connect', namespace='/seasquirt')
def test_connect():
    emit('my response', {'data': 'Connecting', 'count': 0})


@socketio.on('disconnect', namespace='/seasquirt')
def test_disconnect():
    print('Client disconnected', request.sid)

@socketio.on('webcam request', namespace='/seasquirt')
def webcam_server():
    ##os.system("killall mjpg_streamer")
    ##os.system("mjpg_streamer -i 'input_uvc.so -r 1280x720 -f 5' -o 'output_http.so -w /srv/http/wwwwebcam' &")

@socketio.on('reset request', namespace='/seasquirt')
def reset_all():
    global values
    global something_changed
    values = {
        'servo0': 90,
        'servo1': 90,
        'servo2': 90,
        'servo3': 90,
        'servo4': 90,
        'servo5': 90,
        'motor0': 0,
    }
    something_changed = 1




if __name__ == '__main__':
    socketio.run(app, host='0.0.0.0')
