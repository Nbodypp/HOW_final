import numpy as np
import matplotlib.pyplot as plt

n=20
n_part=13

num_beforespeedup,t_beforespeedup = np.loadtxt('output_data/output.beforespeedup.dat',unpack=True)
avg_t_beforespeedup=[]
avg_t_beforespeedup_sigma=[]
for i in range(0,len(t_beforespeedup)/n):
    tempsum = 0.
    templist = []
    for j in range(n):
        tempsum+=t_beforespeedup[i*n + j]
        templist.append(t_beforespeedup[i*n + j])

    avg_t_beforespeedup.append(tempsum/n)
    avg_t_beforespeedup_sigma.append(np.std(templist))


num_index,t_index = np.loadtxt('output_data/output.index.dat',unpack=True)
avg_t_index=[]
avg_t_index_sigma=[]
for i in range(0,len(t_index)/n):
    tempsum = 0.
    templist = []
    for j in range(n):
        tempsum+=t_index[i*n + j]
        templist.append(t_index[i*n + j])

    avg_t_index.append(tempsum/n)
    avg_t_index_sigma.append(np.std(templist))        


num_iterator,t_iterator = np.loadtxt('output_data/output.iterator.dat',unpack=True)
avg_t_iterator=[]
avg_t_iterator_sigma=[]
for i in range(0,len(t_iterator)/n):
    tempsum = 0.
    templist = []
    for j in range(n):
        tempsum+=t_iterator[i*n + j]
        templist.append(t_iterator[i*n + j])

    avg_t_iterator.append(tempsum/n)
    avg_t_iterator_sigma.append(np.std(templist))


num_used_index = []
num_used_iterator = []
num_used_beforespeedup = []
print len(num_index)
print len(num_iterator)
print len(num_beforespeedup)
for i in range(n_part):
    num_used_index.append(num_index[i*n])
    num_used_iterator.append(num_iterator[i*n])
    num_used_beforespeedup.append(num_beforespeedup[i*n])

    
plt.scatter(num_used_beforespeedup,np.divide(avg_t_beforespeedup,1e3),label="Before speedup",color='b')
plt.errorbar(num_used_beforespeedup,np.divide(avg_t_beforespeedup,1e3),yerr=np.divide(avg_t_beforespeedup_sigma,1e3),color='b',linestyle="None",capsize=6)
plt.scatter(num_used_index,np.divide(avg_t_index,1e3),label="Index",color='r')
plt.errorbar(num_used_index,np.divide(avg_t_index,1e3),yerr=np.divide(avg_t_index_sigma,1e3),color='r',linestyle="None",capsize=6)
plt.scatter(num_used_iterator,np.divide(avg_t_iterator,1e3),label="Iterator",color='g')
plt.errorbar(num_used_iterator,np.divide(avg_t_iterator,1e3),yerr=np.divide(avg_t_iterator_sigma,1e3),color='g',linestyle="None",capsize=6)

#plt.xscale(u'log')
#plt.yscale(u'log')

#plt.xlim(left=0.95)

plt.xlabel("Number of particles")
plt.ylabel("Run time in seconds")

plt.legend(loc='upper left')

plt.savefig("scaling.comp.pdf")

print avg_t_iterator[-1]
print avg_t_beforespeedup[-1]
plt.close()
