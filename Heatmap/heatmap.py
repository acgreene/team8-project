import serial
import numpy as np
import seaborn as sns
import matplotlib.pyplot as plt

ser = serial.Serial(port = "/dev/cu.usbserial-0001", baudrate = 115200, timeout = 1)
while(ser.readline().decode("utf-8") != ""): continue
ser.readline()
ser.readline()

frame = np.zeros((8,8))
for i in range(8):
    line_str = ser.readline().decode("utf-8")
    frame[i] = np.array(line_str.split(), dtype = float)
ser.close()

ax = sns.heatmap(frame)
plt.show()
