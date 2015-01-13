#Plots the orbit of the moon and the earth around the pseudo-sun

import numpy as np
import matplotlib.pyplot as plt

earth = np.loadtxt("run.dat",usecols=(0,1),unpack=True)
moon = np.loadtxt("run.dat", usecols=(9,10),unpack=True)

plt.plot(np.divide(earth[0],1e12),np.divide(earth[1],1e12),c='blue',lw=.5)
plt.plot(np.divide(moon[0],1e12),np.divide(moon[1],1e12),c='red',lw=.25)


plt.rc('text',usetex=True)
plt.xlabel("X distance in $10^{12}$  cm")
plt.ylabel("Y distance in $10^{12}$  cm")

plt.savefig("earthmoon.orbit.pdf")
