#!/usr/bin/env python
# encoding: utf-8
"""
make plots for energy test
"""
import sys
import matplotlib.pyplot as plt
import numpy as np

plt.rc('lines', linewidth=1)
plt.rc('mathtext', default='regular')

fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(8, 4))
plt.subplots_adjust(left=0.1, bottom=0.15, right=0.95, top=0.95)

for fn in sys.argv[1:]:
    d = np.loadtxt(fn)
    if 'energy' in fn:
        ax1.plot(np.arange(1, d.size), np.abs((d[1:] - d[0]) / d[0]), label=fn)
    elif 'orbit' in fn:
        x, y = d[::10, 9:11].T
        ax2.plot(x, y, label=fn)
        if 'leapfrog' in fn:
            lim = np.max(np.max(x), np.max(y))

ax1.set_xlabel('time step')
ax1.set_ylabel('$\delta E / E$')
ax1.set_xscale('log')
ax1.set_yscale('log')
ax1.legend(loc='upper left', fontsize=10)

ax2.set_xlim(-lim, lim)
ax2.set_ylim(-lim, lim)

plt.savefig('test.png', dpi=120)
