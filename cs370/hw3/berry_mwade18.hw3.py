# probs2_2.py
# Mitchell Wade
# mwade18
# 7/18/16

#!/opt/local/bin/python3.3
#######################################################
# probs2_2.py
# 
# Scripts corresponding to problems 12, 17, and 18 on
# pages 79-82.
######################################################
from numpy import array,zeros,dot,linalg,float64,transpose
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

#W = array((3,1), float)
k = array((3,1), float)
a = zeros((3,3), float)
k1=k3=k4=1.
k2=k5=2.
w1=w3=2.
w2=1.
a[0,0] = k1+k2+k3+k5
a[0,1] = -k3
a[1,0] = -k3
a[0,2] = -k5
a[2,0] = -k5
a[1,1] = k3+k4
a[1,2] = -k4
a[2,1] = -k4
a[2,2] = k4+k5
L = choleski(a)
# MB: you never defined the W array for this function:
W = array([w1, w2, w3])  # MB: this will produce the correct results.
x = choleskiSol(L,W)
print("Displacements are (in units of W/k):",x)
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
   #i1 = r+30+20 MB: these are what you are solving for
   #i2 = r+50+15
   #i3 = 120+30+15+0
   a = zeros([3,3])

   b = array([0,0,120], float)   # MB: You never defined this

#  a[0,:] = (50*i1)+(r*i1)-(r*i2)-(30*i3)  # MB: You are setting the entire row
#  a[1,:] = (-r*i1)+((65+r)*i2)-(15*i3)    #      to one value
#  a[2,:] = (-30*i2)-(15*i2)+(45*i3)

   a[0,:] = [50.+r,-r,-30.]  # MB: Here is how to create the coeff matrix given R
   a[1,:] = [-r,65.+r,-15.]
   a[2,:] = [-30.,-15.,45.]

#  b = array((1,3), float)  <- this was your code but b has no values

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

# Obviously, you did not do this problem. (-10 points)
a = zeros([4,4])
a[0,:] = 0
a[1,:] = 0
a[2,:] = 0
a[3,:] = 0
b = array(0)
print("The currents are (in amps):\n",gaussElimin(a,b))

input("Press return to exit")
