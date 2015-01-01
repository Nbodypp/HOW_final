import numpy as np
import matplotlib.pyplot as plt

m_earth = 3.01473e-6
m_moon = 3.70907e-8

kmperau = 149597871. * 1e-3 *3.4318965# 10^3 km per 3.43 au

def center_of_mass_loc(rex,rey,rmx,rmy):

        x = (m_earth * rex + m_moon * rmx)/(m_earth + m_moon)
        y = (m_earth * rey + m_moon * rmy)/(m_earth + m_moon)
        #z = (m_earth * re[2] + m_moon * rm[2])/(m_earth + m_moon)

        return np.asarray( [x,y] )

#earth = np.loadtxt("run.dat",usecols=(0,1),unpack=True)
#moon = np.loadtxt("run.dat", usecols=(9,10),unpack=True)

earth = np.loadtxt("run.dat",usecols=(0,1),unpack=True)
moon = np.loadtxt("run.dat", usecols=(9,10),unpack=True)


num=1000
for i in range (len(earth[0])):
    if i%num == 0:
        center = center_of_mass_loc(earth[0][i],earth[1][i],moon[0][i],moon[1][i])
        plt.scatter(kmperau*(earth[0][i] - center[0]), kmperau*(earth[1][i] - center[1]),c='blue',s=60)
        plt.scatter(kmperau*(moon[0][i] - center[0]), kmperau*(moon[1][i] - center[1]),c='black',s=30)
        norm_x = earth[0][i]/np.sqrt( earth[0][i]*earth[0][i] + earth[1][i]*earth[1][i])

        norm_y = earth[1][i]/np.sqrt( earth[0][i]*earth[0][i] + earth[1][i]*earth[1][i])

        emdist = 4.5e2 #in 10^3 km

        print str(norm_x) + "   " + str(norm_y)

        plt.arrow(-emdist+1.e2,-emdist+1.e2,-emdist * .15 * norm_x,-emdist * .15 * norm_y,head_width=30,head_length=30,color='black')

        tempstring = "png/earthmoon." + str(i/num) + ".png"
#        plt.xlim(-emdist,emdist)
#        plt.ylim(-emdist,emdist)
        plt.savefig(tempstring)
        plt.close()
        print str(i/num) + " done"


