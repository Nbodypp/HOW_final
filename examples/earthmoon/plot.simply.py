import numpy as np
import matplotlib.pyplot as plt

earth = np.loadtxt("run.dat",usecols=(0,1),unpack=True)
moon = np.loadtxt("run.dat", usecols=(9,10),unpack=True)

plt.plot(earth[0],earth[1],c='green')
plt.plot(moon[0],moon[1],c='black')

plt.show()
