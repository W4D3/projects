# handicap.py
# Mitchell Wade
# April 3, 2015
# This program calculates the handicap for golfers based
# off of their scores from a score list and a handicap
# that is calculated based on the scores and a course from
# a course list.
# argv[1] = score-file
# argv[2] = course-file

import sys
from decimal import Decimal
from datetime import datetime

if (len(sys.argv) != 3):
    print "usage: python handicap.py score-file course-file"
    sys.exit()

# Create two lists
courses = {}
golfers = {}

def readGolfersFile(fn):
    f = file(fn)
   
    for line in f:
        l = line.split()

        golfdate = datetime.strptime(l[0] + ' ' + l[1] + ' ' + l[2], '%m %d %Y')
        course = "".join(word + " " for word in l[5:len(l)]).strip()

        if l[3] not in golfers:
            golfers[l[3]] = { "handicap": -1, "rounds": {} }
    
        golfers[l[3]]["rounds"][golfdate] = ( Decimal(l[4]) - courses.get(course)[0] ) * 113/ courses.get(course)[1]

    f.close()

def readCourseFile(fn):
    f = file(fn)
    curcourse = ""

    for line in f:
        l = line.split()

        if len(l) > 0:
            if l[0] == "Course":
                curcourse = "".join(word + " " for word in l[1:len(l)]).strip()
            if l[0] == "Rating":
                courses[curcourse] = ( Decimal(l[1]), Decimal(l[3]) )
    f.close()

def computeHandicaps():
    for golfer in golfers:
        
        if len(golfers[golfer]["rounds"]) < 20:
            continue
        
        lowest10 = []
        
        for key, value in sorted(golfers[golfer]["rounds"].items(), key = lambda x: x[0], reverse = True)[0:20]:
            lowest10.append(value)
        
        lowest10.sort()
        avg = Decimal(0.0)
        
        for value in lowest10[0:10]:
            avg = avg + value
        
        avg = avg / 10
        golfers[golfer]["handicap"] = Decimal(0.96) * avg

# Call the cmdline functions to read in info and
# compute the handicaps
readCourseFile(sys.argv[2])
readGolfersFile(sys.argv[1])
computeHandicaps()

# Sort the golfers based by handicap
sorted_golfers = sorted(golfers.items(), key = lambda x : x[1]["handicap"])

# Print out the golfers and their handicaps
for key, value in sorted_golfers:
    if value["handicap"] == Decimal(-1):
        continue
    print '{1:>5.2f} {0:s}'.format(key, value["handicap"])

