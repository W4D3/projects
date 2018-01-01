from numpy import *                                                           
def funct2(nMax) :
   r=[] 
   for n in range(0,nMax): 
      r.append(n*2)  
   k=r[:] 
   k[1]+=3 
   print(r[1],k[1]) 
funct2(4)
