from numpy import *
def funct2(nMax):
   r=[]
   for n in range(0,nMax):
      r.append(n*2)
   h=r
   k=r[:]
   h[0]+=2
   k[1]+=3
   m=[h,k]
   print(m[1][2])
funct2(4)
