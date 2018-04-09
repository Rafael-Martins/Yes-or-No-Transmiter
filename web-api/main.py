import serial
from threading import Thread
from flask import Flask


ser = serial.Serial('COM3', 9600)
value = ""

class Th(Thread):

    def __init__ (self):
      Thread.__init__(self)

    def run(self):
        while True:
            global value
            value = ser.readline().decode("utf-8").split("'")[0].split("/")[0].rstrip()
            print (value)

Th().start()

app = Flask(__name__)

@app.route("/")
def hello():
    print (value)
    return value

if __name__ == "__main__":
    app.run()
