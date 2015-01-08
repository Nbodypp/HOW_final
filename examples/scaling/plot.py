import numpy as np
import matplotlib.pyplot as plt

#Note: output from run.sh script needs to have :
num,t = np.loadtxt('output.dat',unpack=True)

#plt.plot(num,t)
plt.scatter(num,np.divide(t,1e3))

plt.xlabel("Number of particles")
plt.ylabel("Run time in seconds")

def n_factorial(x):
    temp = []
    for val in x:
        temp.append(np.math.factorial(val))        
    return np.asarray(temp)

num_finer=np.arange(num[0],num[-1]+1)

#model = np.multiply(n_factorial(num_finer),5.32e-35)
#plt.plot(num_finer,model)

plt.savefig("scaling.png")
plt.close()
