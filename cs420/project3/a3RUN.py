# Generate 50 random bipolar vectors (N = 100)
import random
import pprint
import time

pp = pprint

startTime = time.time()

vector = list(range(100))
vectorList = list(vector*50)
bipolar = [-1, 1]
for i in vectorList:
   for j in vector:
      bipolar = [-1, 1]
      rand = random.choice(bipolar)
      vector[j] = rand
   vectorList += vector

print(" Vector Initialization Time = " % (time.time() - startTime))

# For p = 1, ..., 50, imprint the first p patterns on a Hopfield net.
#for i in vector:
   # Compute Weights associated with the neurons, which you will use to 
   # calculate the net input (local field) in a later step.
   # weight = (1/100)

# def sum(si, sj):
   # for k in range(p+1, p):
   # for k in enumerate(range(p+1, p)):

# Determine pstable, the number of stable imprinted patterns.  A pattern is considered unstable if any of its bits are unstable, that is, of opposite sign to their local field hi.  Compute the probability of an imprinted pattern being stable, Pstable = pstable / p.  (Note that Pstable and pstable are different; this is Bar-Yam's notation, which I've retained for consistency with the book.)

# Repeat the forgoing for several sets of 50 random patterns and average over them.

# As a result of your simulations, you should generate two graphs:  First, a plot of the fraction of unstable imprints as a function of the number of imprints (p = 1, ..., 50).  Second, a plot of the number of stable imprints as a function of the number of imprints (eame range).

# For additional information see Bar-Yam Section 2.2.6 (pages 312-14); your program should be able to generate graphs comparable to Figs. 2.2.5 and 2.2.6 (but it is not necessary to normalize to p).

# You should hand in (1) your program, (2) your graphs or other output, and (3) a discussion of your results and their implications.

# For extra credit, do some or all of the activities described below For Graduate Credit.
