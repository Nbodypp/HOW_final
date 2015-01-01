import sys
import pylab as pl
import argparse

parser = argparse.ArgumentParser(
        description='Plot orbit data on x-y, y-z, x-z plane')
parser.add_argument('filename', type=str)
parser.add_argument('-s', '--scale', type=float,
                    help='scale length', default=1.)
args = parser.parse_args()

d = pl.loadtxt(args.filename).T

fig, axs = pl.subplots(2, 2)
for p in pl.split(d, d.shape[0]/9):
    x, y, z, vx, vy, vz, ax, ay, az = p
    x /= args.scale
    y /= args.scale
    z /= args.scale
    axs[0,0].plot(x[::], y[::], '.')
    axs[0,1].plot(x, z, ',-')
    axs[1,0].plot(y, z, ',-')

axs[0,0].set_xlabel('x')
axs[0,0].set_ylabel('y')

axs[0,1].set_xlabel('x')
axs[0,1].set_ylabel('z')

axs[1,0].set_xlabel('y')
axs[1,0].set_ylabel('z')
pl.show()
