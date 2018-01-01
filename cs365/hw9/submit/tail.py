# tail.py
# Mitchell Wade
# March 24, 2015
# This program prints the last n lines of a file. It
# takes two cmd line arguments which are the name of
# the file and the num of lines to print

import sys

if (len(sys.argv) != 3):
    print "usage: python tail.py filename numlines"
    sys.exit()

file = open(sys.argv[1])
n = int(sys.argv[2])

lines = list(file)

for line in file:
    lines.append(line.strip())

for line in lines[-n:]:
    print line
