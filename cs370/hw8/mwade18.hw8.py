#!/usr/bin/env python3
# Template for COSC 370 Hwk #8
# Approximation of derviatives using FDA, Richardson extrapolation,
# and polynomial interpolation
#
from numpy import round, array, polyfit, polyder, polyval
#
# Problem 5.1.9
#
print("Problem 5.1.9\n=============")
#
# This is an example of a dictionary with key:value pairs,
# data9[0.1]=0.078348 and data9[0.3]=0.192916, for example.
#
data9 = { 0.0: 0.0, 0.1: 0.078348, 0.2: 0.138910, 0.3: 0.192916, 0.4: 0.244981 }
#
# We want to approximate f'(0.2) using two different values of h (=0.2, 0.1)
#
# First use central difference FDA, i.e., 2hf'(x) = -f(x-h) + f(x+h), with h=0.2
#
h1 = 0.2
x = 0.2
#centralApprox1 = (-f(x-h1) + f(x+h1))/2*h1
#centralApprox1 = (-f(0.2-0.2) + f(0.2+0.2))/2*0.2
#centralApprox1 = (-f(0) + f(0.4))/0.4
#centralApprox1 = (-0 + 0.244981)/0.4
centralApprox1 = (-(data9[x-h1]) + data9[x+h1])/(2*h1)
print("Central FDA Approximation (h = 0.2): %f" % centralApprox1)
#
# Now, half the stepsize and set h=0.1
# and use the function all round(x+h2, decimals=1) so that you can
# insure the proper key from the data9 dictionary will be selected.
#
h2 = h1 / 2.0
centralApprox2 = (-(data9[round(x-h2, decimals=1)]) + data9[round(x+h2, decimals=1)])/(2.0*h2)
#print(centralApprox2)
#
# Now, apply Richardson Extrapolation to improve the approximation of f'(0.2)
# using centralApprox1 and centralApprox2
p = 2.0
#richardsonExtrap = (((h1/h2)^p)*(g(h2) - g(h1)))/(((h1/h2)^p)-1)
#richardsonExtrap = ((2^p)*(g(h1/2) - g(h1)))/((2^p)-1)
richardsonExtrap = ((2**p)*(centralApprox2) - centralApprox1)/((2**p)-1)
#richardsonExtrap = (-(data9[round(x-h2, decimals=1)]) + \
#                      data9[round(x+h2, decimals=1)])/round((2.0*h2), decimals=1)
print("Richardson Extrapolation (h2 = h1 / 2, p = 2): %f" % richardsonExtrap)
#
# Problem 5.1.11
#
print("\nProblem 5.1.11\n==============")
#
# Here are the interpolation data points...
#
xData = array([-2.2, -0.3, 0.8, 1.9])
yData = array([15.18, 10.962, 1.92, -2.04])

# Using polyfit and polyder from Numpy...

# First compute the coefficients for a cubic interpolating
# polynomial using polyfit

p = polyfit(xData, yData, 3)
#
# Then, use those coefficients to construct the first (d1) and
# second (d2) derivative functions via polyder...
#

d1 = polyder(p, 1) 
d2 = polyder(p, 2)
#
# Here are the coeffcients of the actual polynomial, whose derivatives
# we are approximating.
#
pActual = array([1, -0.3, -8.56, 8.448])

# Use those coefficients to construct the first (d1Actual) and
# second (d2Acutal) derivative functions via polyder...

d1Actual = polyder(pActual, m=1)
d2Actual = polyder(pActual, m=2)

# Now, evaluate the first derivative of your cubic interpolating polynomial
# at x=0, and then do the same for the first derivative of the actual
# polynomial whose coefficients are given in pActual.

fd = polyval(d1, x=0)
fdActual = polyval(d1Actual, x=0)

print("Interpolated f'(0): %f" % fd)
print("Actual f'(0): %f" % fdActual)
print("Error: %f\n" % (fdActual - fd))

# Now, evaluate the second derivative of your cubic interpolating polynomial
# at x=0, and then do the same for the second derivative of the actual
# polynomial whose coefficients are given in pActual.

sd = polyval(d2, x=0)
sdActual = polyval(d2Actual, x=0)

print("Interpolated f''(0): %f" % sd)
print("Actual f''(0): %f" % sdActual)
print("Error: %f" % (sdActual - sd))
#
# Outputs for verification:
#
# Problem 5.1.9
# =============
# Central FDA Approximation (h = 0.2): 0.612452
# Richardson Extrapolation (h2 = h1 / 2, p = 2): 0.559636
#
# Problem 5.1.11
# ==============
# Interpolated f'(0): -8.560000
# Actual f'(0): -8.560000
# Error: -0.000000
#
# Interpolated f''(0): -0.600000
# Actual f''(0): -0.600000
# Error: -0.000000
