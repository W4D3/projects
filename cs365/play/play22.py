import sys
sum = 0
try:
    for line in sys.stdin:
        values = line.strip().split()
        for v in values:
            sum = sum + int(v)
except ValueError as e:
    print "could not convert data to an int"
else:
    print 'sum =', sum
finally:
    print 'finishing up'
print 'sum =', sum
