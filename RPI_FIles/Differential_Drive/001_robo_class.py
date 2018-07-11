"""
Defining the differential driving kinematics of NOMO.
This file contains a class for the Robot and for Differential drive as well for sensors and actuators.

copyright 2018. Vishnu Pradeesh.
"""
import numpy as np
import matplotlib.pyplot as plt
from scipy.integrate import odeint
from matplotlib import animation

r = 0.1
L = 1.0

def system(q, t, dt):
    wr, wl = 100.0, 0.0
    p0 = r/2*(wr+wl)*np.cos(q[2])*dt + q[0]
    p1 = r/2*(wr+wl)*np.sin(q[2])*dt + q[1]
    p2 = r/L*(wr-wl)*dt+q[2]
    return np.array([p0, p1, p2])

trajectory = np.array([[0.0, 0.0, 0.0]])
dt = 0.01
tspan = np.arange(0, 100, dt)
n = len(tspan)

for n,t in enumerate(tspan):
    trajectory = np.vstack([trajectory, system(trajectory[n], t, dt)])

xmin, xmax = trajectory[:, 0].min(), trajectory[:, 0].max()
ymin, ymax = trajectory[:, 1].min(), trajectory[:, 1].max()

fig = plt.figure()
ax = plt.axes(xlim=(xmin,xmax), ylim=(ymin, ymax))
line, = ax.plot([], [], lw=2)

def init():
    line.set_data([], [])
    return line,

def animate(i):
    x, y = trajectory[0:i,0], trajectory[0:i,1]
    line.set_data(x, y)
    return line,

anim = animation.FuncAnimation(fig, animate, init_func=init, frames=n, interval=1, blit=True)
plt.show()