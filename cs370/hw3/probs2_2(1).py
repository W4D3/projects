#!/opt/local/bin/python3.3
#######################################################
# probs2_2.py
# 
# Scripts corresponding to problems 12, 17, and 18 on
# pages 79-82.
######################################################
from numpy import array,zeros
from choleski import *
from gaussElimin import *

## problem2_2_12
######################################################
# 1. Populate k, W, and a below with the values from
#    problem 12 on page 79.
#
# Correct Output: 
# [ 1.66666667  2.66666667  2.66666667]
#
######################################################

k = array([1,2,1,1,2],float)
W = array([2,1,2],float)
a = zeros((3,3))
a[0,0] = k[0] + k[1] + k[2] + k[4]
a[0,1] = a[1,0] = -k[2]
a[0,2] = a[2,0] = -k[4]
a[1,1] = k[2] + k[3]
a[1,2] = a[2,1] = -k[3]
a[2,2] = k[3] + k[4]
L = choleski(a)
x = choleskiSol(L,W)
print("Displacements are (in units of W/k):\n",x)
print("--------------------------------------------")

## problem2_2_17
######################################################
# 1. Populate a and b below with the values from
#    problem 17 on page 82.
#
# Correct Outputs:
# R = 5.0 ohms
# The currents are (in amps):
# [ 2.82926829 1.26829268 4.97560976]
# R = 10.0 ohms
# The currents are (in amps):
# [ 2.66666667 1.33333333 4.88888889]
# R = 20.0 ohms
# The currents are (in amps):
# [ 2.4516129 1.41935484 4.77419355]
#
######################################################

R = [5.0, 10.0, 20.0]
for r in R:
   a = zeros([3,3])
   a[0,:] = [50.0 + r, -r, -30.0]
   a[1,:] = [-r, 65.0 + r, -15.0]
   a[2,:] = [-30.0, -15.0, 45.0]
   b = array([0.0, 0.0, 120.0])
   print("\nR =",r,"ohms")
   print("The currents are (in amps):\n",gaussElimin(a,b))
print("--------------------------------------------")

## problem2_2_18
######################################################
# 1. Populate a and b below with the values from
#    problem 18 on page 82.
#
# Correct Output:
# The loop currents are (in amps):
# [-4.18239492 -2.66455194 -2.71213323 -1.20856463]
######################################################

a = zeros([4,4])
a[0,:] = [80.0, -50.0, -30.0, 0.0]
a[1,:] = [-50.0, 100.0, -10.0, -25.0]
a[2,:] = [-30.0, -10.0, 65.0, -20.0]
a[3,:] = [0.0, -25.0, -20.0, 100.0]
b = array([-120.0, 0.0, 0.0, 0.0])
print("The currents are (in amps):\n",gaussElimin(a,b))

input("Press return to exit")

