# frequency.py
# Mitchell Wade
# April 2, 2015
# This program takes input from a file off the cmd
# line and prints out the frequency of each word in
# the file

import sys
import operator

# Check for proper usage
if (len(sys.argv) != 2):
    print "usage: python frequency.py filename"
    sys.exit()

# Opens the file from cmdline arg 1
file = open(sys.argv[1])

# Creates a dictionary
dict = {}

# Use the file and close it
with file as f:
    for line in f:
        for word in line.split():
            
            # Count occurance of each word and
            # store in a dict
            try:
                dict[word] += 1
            except KeyError:
                dict[word] = 1

# Sort the dict by value and then by the key
sorted_dict = sorted(dict.items(), key = operator.itemgetter(1, 0))

# Print the frequency of each word in the dict
for key, value in sorted_dict:
    print "{0:<20} {1:>5}".format(key, value)
