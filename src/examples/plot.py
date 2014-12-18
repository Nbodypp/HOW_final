import numpy as np
import matplotlib.pyplot as plt

# Some adjustable parameters

skip = 500 #how many timesteps to skip between plots
filename = "sunEarthMoon.earlytest.dat" #Input file name

ncols = 9 #Constant, number of columns per object in file

sun=np.loadtxt(filename,usecols=(0,1),unpack=True)
earth=np.loadtxt(filename,usecols=(ncols,ncols+1),unpack=True)
moon=np.loadtxt(filename,usecols=(2*ncols,2*ncols+1),unpack=True)

for i in range(len(sun[0])):
    if i%skip ==0:
        plt.scatter(sun[0][i],sun[1][i],c='yellow',marker='o',alpha=1,s=60)
        plt.scatter(earth[0][i],earth[1][i],c='blue',marker='.')#,alpha=1,s=20)
        plt.scatter(moon[0][i],moon[1][i],c='gray',marker='.')#,alpha=1,s=10)

        tempstring = "png/sunEarthMoon." + str(i/skip) + ".png"
        plt.savefig(tempstring)
        plt.close()
        print str(i/skip) + " done"
