# Mitchell Wade
# mwade18
# 7/25/16
# ...

#!/usr/bin/env python3
#
# Template for Problems 17 and 19 in Problem Set 3.1 (Hwk #5)
#
# Problem 17 (use log-log scale)
#
from cubicSpline import *
from numpy import array,log10
xData = array([0.2, 2.0, 20.0, 200.0, 2000.0, 20000.0])
yData = array([103.0, 13.9, 2.72, 0.8, 0.401, 0.433])
Re_array= array([5.0, 50.0, 500.0, 5000.0])
logxData = log10(xData)
logyData = log10(yData)
#
# Generate curvatures here
#
k = curvatures(logxData,logyData)
#print(k)

print('\nInterpolating for drag coefficients (C_D)...\n    Re\tC_D')

#
# Create a loop to evaluate the Cubic Spline for the elements
# in the Re_array 
#
for re in Re_array:
   logy = evalSpline(logxData,logyData, k, log10(re))
   print('{:6.1f}\t{:5.3f}'.format(re,10.0**logy)) # Re is an element from

#
# Problem 19 (do not use log-log scale)
#
tData = array([0.0, 21.1, 37.8, 54.4, 71.1, 87.8, 100.0])
mData = array([1.79, 1.13, 0.696, 0.519, 0.338, 0.321, 0.296]) 
T_array = array([10.0, 30.0, 60.0, 90.0])
#
# Generate curvatures here
#
k = curvatures(tData,mData)

print('\nInterpolating for kinematic viscosity (CMu_k)...\n    T\tMu_k')

#
# Create a loop to evaluate the Cubic Spline for the elements
# in the T_array
#
for temp in T_array:
   y = evalSpline(tData, mData, k, temp)
   print('{:6.1f}\t{:5.3f}'.format(temp,y)) # temp is an element from 
                                           # T_array
