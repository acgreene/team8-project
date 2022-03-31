import serial
import numpy as np
import seaborn as sns
import matplotlib.pyplot as plt
import scipy.ndimage

ser = serial.Serial(port = "/dev/cu.usbserial-0001", baudrate = 115200, timeout = 1)

interp = False

for f in range(30):
    l = ser.readline().decode("utf-8")

l = "something"
while(l != '\r\n'): 
    l = ser.readline().decode("utf-8")


grid_kws = {'width_ratios': (0.9, 0.05), 'wspace': 0.2}
fig, (ax, cbar_ax) = plt.subplots(1, 2, gridspec_kw = grid_kws,figsize = (10, 8))

for f in range(1000):
    frame = np.zeros((8,8))
    for i in range(8):
        line_str = ser.readline().decode("utf-8")
        frame[i,:] = np.array(line_str.split(), dtype = float)
    ser.readline()
    if interp:
        frame = scipy.ndimage.zoom(frame, 2, order=3)
    sns.heatmap(ax = ax, data = np.flip(frame, axis = 1), vmin = 65, vmax = 90, cbar_ax = cbar_ax, cmap = 'plasma')
    plt.draw()
    plt.pause(.1)
ser.close()


