#!/usr/bin/python
####################################################################
# problem2_1_15  (Problem Set 2.1, No. 15 on page 53 of textbook)
# This problem requires the LUdecomp.py module (provided).
#
# Fill in the following template. First, determine the value for
# the tolerance variable TOL.  Then, add the code that creates the
# Matrix (a) and the vector (b). Finally, add the code that computes
# the LU decomposition and produces a solution vector (see the
# provided LUdecomp.py module for correct function calls to do that).
####################################################################
import numpy as np

from numpy import zeros, ones, array, float64, inf
from numpy import linalg
from LUdecomp import *

# Read in the number of equations from the cmd line
n = input('Input n (number of equations): ')

# Determine the norm of the number of equations
norm = linalg.norm

# Use the norm to find the tolerance of the linear system even though its
# not necessary with our problem statement
eps = norm(n)
TOL = float(1e-06)
err = 0 
n = 0
while err < TOL:
  n += 1
  a = zeros((n,n),dtype=float64)  # Creates an n*n array with all 0 elem.
  b = zeros((n),dtype=float64)    # Creates an array of size n with all 0 elem.
  soln = ones((n), dtype=float64) # The correct solution is all 1's

  # USE THE LOOPS BELOW TO DEFINE THE MATRIX 'a' AND THE VECTOR 'b':
  for i in range(n):
    for j in range(n):
      try:
         a[i,j] = 1.0/float(i+j-1)    # a = scalars
      except:
         a[i,j] = 1.0
      b[i] += a[i,j]      # b = scalars

  # CALL APPROPRIATE FUNCTIONS FROM THE LUdecomp.py MODULE TO
  # SOLVE THE EQUATIONS A x = b: 
  a = LUdecomp(a) 
  b = LUsolve(a,b)

  # Your solution should be stored in 'b' (if you used a different variable name,
  # modify the code below accordingly).
  #
  print("\n", n, " equations. ", "The solution is:\n", b)
  err = norm(b-soln, ord=inf)
  print("Error (inf-norm of difference)): ", err)

print("^^^(Greater than TOL = ", TOL, ")^^^\n")
print("********************************************\n")
print("Max number of equations while error remains less than ", TOL, " is: ", n-1, "\n") 
print("********************************************")
