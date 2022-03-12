import serial
import numpy as np


ser = serial.Serial(port = "/dev/cu.usbserial-0001", baudrate = 115200, timeout = 1)
for i in range(100):
    line_str = ser.readline().decode("utf-8")
    line = np.array(line_str.split(), dtype = float)
    print(line)
ser.close()
