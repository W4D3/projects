a = 123.456
n = 5789
print ('{:6.2f}'.format(a))
print ('n={:7d}'.format(n))          # pad with 3 spaces
print ('n={:07d}'.format(n))         # pad with 3 zeros
print ('{:11.3e}{:7d}'.format(a,n))  # print tuple with 2 different formats
