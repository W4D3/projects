import sys

# global variable to count number of recursive calls
count = 0

def ackermann(m, n):

   global count
   count+= 1
   
   if m == 0:
      # printf "A(%d,%d)" % (m, n+1)
      return n+1
   elif n == 0:
      # printf "A(%d,%d)" % (m-1, 1)
      return ackermann(m-1, 1)
   else:
      # printf "A(%d,A(%d,%d))" % (m-1, m, n-1)
      return ackermann(m-1, ackermann(m, n-1))

if __name__ == "__main__":
   m = long(sys.argv[1])
   n = long(sys.argv[2])

   count = 0

   rv = ackermann(m, n)
   print "Result: %d (%d recursive calls)" % (rv, count)
