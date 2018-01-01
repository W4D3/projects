# Mitchell Wade
# mwade18
# 8/8/16
# ...

#!/usr/bin/env python3
#
# Template script for Problem 14 from Problemt Set 6.1 (p. 214 of textbook)
#  
from romberg import *
from numpy import *
#from numpy import range
#from numpy import arange
import matplotlib.pyplot as plt

def f(x):
  if x == 0: return 0
  # define the integrable function here
  else: return ((x**4)*exp(x))/((exp(x)-1)**2)

#
#for i in range(0,1.01,0.5):
#  u.append(i)
#print u
#

#
#u = []
#for i in range(0,1.01):
#  if i%0.5 != 0: continue
#  u.append(i)
#print u
#

u = arange(0,1.01,0.05)

print("    u\t   g(u)")
gu = [] #list that will contain all of g(u)s (y-coordinates for your plot)

for i in u:
  if i == 0: g = 0.0;
  else:
    I,nPanels = romberg(f, 0, 1/i)
                     # perform romberg integration on f here (get result in
                     # I, nPanels is the number of panels used but is not
                     # used for output.

    #print(I)
    #print(nPanels)
    # Number of particles in the solid
    #N = nPanels

    # Boltzmann constant
    #k = R/N_A
    #k = 1.38064852e-23

    # Absolute temperature
    #T = 1/2kT
    #T = 2.07e-21

    # Debye temperature
    #theta(D) = ???

    # u = T/theta(D)
    #u = T/theta_D

    # Function to be evaluated
    g = ((i**3)*I)   # evaluate g(i) here

    # Heat capacity as a solid
    #C_v = 9*N*k*gu

  print ('{:6.2f}{:13.6f}'.format(i,g))
  gu.append(g)
#
# Place the code that creates the required plot using pylab here.
# Be sure to label axes and provide the same title as shown
# in the "prob6_1-14.png" image file on BB
plt.plot(u,gu,"b-")
#plt.axis([0.0,0.2,0.4,0.6,0.8,1.0]
plt.grid()
plt.xlabel('u')
plt.ylabel('g(u)')
plt.title('Problem 6.1.14')
plt.show()

# Table written to stdout for verification purposes:
#
#  u	     g(u)
# 0.00     0.000000
# 0.05     0.003247
# 0.10     0.025274
# 0.15     0.070997
# 0.20     0.122878
# 0.25     0.167686
# 0.30     0.202568
# 0.35     0.228858
# 0.40     0.248618
# 0.45     0.263608
# 0.50     0.275136
# 0.55     0.284136
# 0.60     0.291265
# 0.65     0.296992
# 0.70     0.301651
# 0.75     0.305487
# 0.80     0.308678
# 0.85     0.311359
# 0.90     0.313631
# 0.95     0.315573
# 1.00     0.317244

