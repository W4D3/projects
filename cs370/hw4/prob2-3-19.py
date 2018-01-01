# Mitchell Wade
# mwade18
# 7/21/16
# HW4

#!/usr/bin/env python3
# prob2-3-19 (hwk #4)
#
#  Problem 2.3.19 (pg. 101)
#
#  1) Implement the Ax(v) function below so that it will initialize
#     and return the matrix-vector product Ax, where A is given at
#     the top of page 101 in the textbook.
#  
#  2) Use the provided conjGrad.py module to solve the system described
#     in problem #19 (uncomment and fill in the '??' lines).
#
# The correct solution is:
#
# [ 21.42857143 38.39285714  57.14285714   47.32142857   75.
#   90.17857143 92.85714286 124.10714286 128.57142857]
#
########################################################################

from numpy import zeros,array,linalg,ones
from conjGrad import *
#from LUdecomp3 import *
# Refer to pg. 101 for what the matrix Ax should be

def Ax(v):
   # fill in the 9 rows of Ax
   n = len(v)
   Ax = zeros((n))
   #g = ones((6))*(1.0)
   #print(g)
   #f = zeros((7))*(0.0)
   #print(f)
   #e = ones((8))*(1.0)
   #3e[3] = 0.0
   #e[6] = 0.0
   #print(e)
   #d = ones((9))*(-4.0)
   #print(d)
   #c = ones((8))*(1.0)
   #c[3] = 0.0
   #c[4] = 0.0
   #c[6] = 0.0
   #print(c)
   #B = zeros(7)*(0.0)
   #print(B)
   #A = ones(6)*(1.0)
   #print(A)
   #Ax[0,:] = [-4.,1.,0.,1.,0.,0.,0.,0.,0.]
   #Ax[1,:] = [1.,-4.,1.,0.,1.,0.,0.,0.,0.]
   #Ax[2,:] = [0.,1.,-4.,0.,0.,1.,0.,0.,0.]
   #Ax[3,:] = [1.,0.,0.,-4.,1.,0.,1.,0.,0.]
   #Ax[4,:] = [0.,1.,0.,0.,-4.,1.,0.,1.,0.]
   #Ax[5,:] = [0.,0.,1.,0.,1.,-4.,0.,0.,1.]
   #Ax[6,:] = [0.,0.,0.,1.,0.,0.,-4.,1.,0.]
   #Ax[7,:] = [0.,0.,0.,0.,1.,0.,1.,-4.,1.]
   #Ax[8,:] = [0.,0.,0.,0.,0.,1.,0.,1.,-4.]
   #A,B,c,d,e,f,g = LUdecomp3(A,B,c,d,e,f,g)
   #for i in range(n):
   #   Ax[:,i] = LUsolve3(A,B,c,d,e,f,g)
   Ax[0] = -v[0]*(4.0)  + v[1]       + v[3]
   Ax[1] =  v[0]        - v[1]*(4.0) + v[2]        + v[4]
   Ax[2] =  v[1]        - v[2]*(4.0) + v[5]
   Ax[3] =  v[0]        - v[3]*(4.0) + v[4]        + v[6]
   Ax[4] =  v[1]        - v[4]*(4.0) + v[5]        + v[7]
   Ax[5] =  v[2]        + v[4]       - v[5]*(4.0)  + v[8]
   Ax[6] =  v[3]        - v[6]*(4.0) + v[7]
   Ax[7] =  v[4]        + v[6]       - v[7]*(4.0)  + v[8]
   Ax[8] =  v[5]        + v[7]       - v[8]*(4.0)
   return Ax

# Actually are there patterns?


# After writing it out this way, I can see the patterns and how I should condense the lines into a Ax[i:n] expression for better precision.


# Dr. Berry, I just realized I should actually read the text book, and I believe that if I
# make changes to the number of operations, the positive or negative coefficents, and other
# small changes then the solution will change. I plan on fixing this, but I want to submit
# now in hopes of getting partial credit or full credit if possible. Also, thanks for the
# heads up even though I was too blind to see what you meant about not getting caught up in
# details of python. I have been missing the point of this class, and pretty much all of my 
# classes because of how I try and take on every burden possible. Going forward, I plan to 
# read appropriately and to give this my all. PLEASE let me know if you have any suggestions.
# Thanks, MBW

b = array([0,0,100,0,0,100,200,200,300])*(-1.0)
x = zeros((9))*1.0
tol = 1e-06
s1,numIter = conjGrad(Ax,x,b,tol)
print("\nThe solution is:\n",s1)
print("\nNumber of iterations =",numIter, "using Tol: ", 1e-06)

print("\n CG Convergence Test")
print("Iterations   Tolerance")
#
# Use the loop below to call conjGrad with various tolerances, 
# compare the number of iterations.
#
for tol in [1e-02, 1e-04, 1e-06, 1e-08, 1e-10, 1e-12, 1e-14, 1e-16]:
  x = zeros((9),dtype=float)
  s2,numIter = conjGrad(Ax,x,b,tol)
  print('%6d      %8.1e'%(numIter,tol))

print("\nError between vectors obtained with tol=1e-06 and tol=1e-16: ", linalg.norm(s1-s2), "\n")
