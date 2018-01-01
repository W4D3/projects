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

# NOTES
# ( A11 A12 ... A1n ) [X1] = [B1]
# ( A21 A22 ... A2n ) [X2] = [B2]
#
# Uniqueness of Solution
# Unique if A is non-singular or det(A) = | A | = 0
#
# If A is singular, then Ax = b has infinite solutions or no solutions
#
# ex) 2x + y  = 3
#     4x + 2y = 6         <--- 2 equations, 2 unknowns
#
#   Row 2 is (2*Row1) <--- R2 = 2*R1
#   This is an example of infinite solutions
#
# ex2) 2x + y  = 3
#      4x + 2y = 0
#
#
#  ( 2 1 )
#  ( 4 2 )   to find the cross product: |A| = (2*2) - (1*4) = 0
#
# If you divide 4x + 2y / 2 then you get 2x + y = 0; however, you can't have
# 2x + y = 3 and it also equal 2x + y = 0 <--- NO SOLUTIONS
#
# Ill-conditioning
# Nearly singular
#
# You can always estimate the norm and you can also estimate by finding the norm
# As the norm gets small it is an upper bound for the determinat, then you can 
# bet that the det will be small <--- therefore the det is ill conditioned
#
#
# |A| << ||A||, where ||A|| is a matrix norm
#
# Forbenius norm = Sqrt[Sum(i = 1 to n)Sum(j = 1 to n) Aij^2]
#
# ||A||infinity = max(1 <= i <= n) Sum(j = 1 to n) | Aij|
# This will find the maximum column sum or how big the elem. are in magnitude
# (max col sum of mag)
#
#  The condition number of A is defined by cond(A0 = ||A|| x ||A^-1||
#
# If cond(A) = 1, then we say A is well-conditioned; cond(A0 is not unique
# depends on the norm you choose
#
# cond(A) is expensive to compute so we typically compare |A| to magnitudes of A
# elem.
#
# similar ex).      2x + y = 3
#                   2x + 1.001y = 0
#
#           ( 2  1     )
#           ( 2  1.001 )  = A
#   therefore, |A| = 0.002 <-- this is very small compared to the elems.
#
#   x = 1501.5
#   y = -3000
#
#   This is not exactly singular
#
#   Singular means det = 0
#
#   The det is so much smaller 
#
#
#   2x + y = 3
#   2x + 1.002y = 0    (delta = 0.001)
#
#   x = 1501.5              x = 751.5
#   y = 3000                y = -1500
#
#   So we see that a 0.1percent change in A yields a 100% change in the sol.
#
#   If you cna do this, you most likely have an ill-conditioned matrix
#
#
#   SOLVING LIN SYSTEMS
#   
#  Direct Methods:       <=== USED FOR SMALL MATRIXS
# 1. Exchange 2 rows (changes sign of |A|
# 2. Multiply equation by nonzero constant a (|A| becomes alpha |A|)
# 3. Multiply equation by nonzero constant a and subtract it from another
# equation (|A| unchanged).
#
# Iterative methods (Indirect Methods):   <=== USED FOR LARGE MATRIX
#   - typically used for large and sparse A (more zeroes than nonzeroes)
# guess sol. and improve every iteration
#
#
# You can take any n*n matrix A and factor it into A = LU
#
# Doolittle Iii = 1, i=1,2,...,n  <-- all 1's lie on the diag I
#                       A = A^transpose
#                       A = U^transpose*U which is (u^transpose*u)^transpose = 
#                                    u^t*u
#       (LU)x = b replace Lu by Lu factorization
#       L(Ux) = b, make sub for y
#       forward sub for b Ly = b
#       back sub for: Ux = y
# Crout Uii = 1,i=1,2,...,n       <-- all 1's lie on the diag U
#
#
#   A can be expressed as A = LU
#   L = lower triangluar matrix
#   U = upper triangular matrix
#
#   Diag matrix of L are 1 for Doolittle
#
#   If you can produce the LU decompositon then, you can replace L
# reorder: (LU)x = b becomes L(Ux) = b, then replace Ux with y, then Ly = b
#  Ux = y (given y solve for Ux = y)

from numpy import zeros, ones, array, float64, inf
from numpy import linalg
from LUdecomp import *

norm = linalg.norm  # Python allows you to rename functions.
                    # Here, 'linalg.norm' is renamed to just 'norm'.
# PROVIDE A VALUE FOR THE VARIABLE TOL THAT MATCHES THE SPECIFICATIONS OF
# THE PROBLEM
TOL = (1+epsilon)       #  should this be epsilon?
err = 0 
n = 0
while err < TOL:
  n +=1
  a = zeros((n,n),dtype=float64)  # Creates an n*n array with all 0 elem.
  b = zeros((n),dtype=float64)    # Creates an array of size n with all 0 elem.
  soln = ones((n), dtype=float64) # The correct solution is all 1's

  # USE THE LOOPS BELOW TO DEFINE THE MATRIX 'a' AND THE VECTOR 'b':
  for i in range(n):
    for j in range(n):
      a[i,j] += n    # a = scalars
      b[i] += a       # b = scalars
                    # x = unknowns

  # CALL APPROPRIATE FUNCTIONS FROM THE LUdecomp.py MODULE TO
  # SOLVE THE EQUATIONS A x = b: 
  #a = ??
  #b = ??

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
