from list import *

x = dlist.DList(lambda a, b: a == b)

# add some elements to the list
x.append("brad")
x.append("minnie")
x.append("pluto")
x.append("fred")
x.append("nancy")
x.append("mary")

# print the list elements
print "the list should be: brad minnie pluto fred nancy mary"
for n in x:
    print n.value
print

# find some list elements and delete them
y = x.find("fred")
x.erase(y)

y = x.find("brad")
x.erase(y)

# print the list elements
print "the list after deleting fred and brad: minnie pluto nancy mary"
for n in x:
    print n.value
print

# find someone not in the list
print "find brad: brad should not be in the list"
if (x.find("brad") == None):
    print "brad not in list"
else:
    print "oops: brad was found--fix this!"
print

# test insertBefore
y = x.find("pluto")
x.insertBefore("terry", y)

y = x.find("mary")
x.insertBefore("jeff", y)

y = x.find("minnie")
x.insertBefore("charlie", y)

y = x.find("jeff")
x.insertBefore("cheryl", y)

# print the list elements
print "list after insertBefore: charlie minnie terry pluto nancy cheryl jeff mary"
for n in x:
    print n.value
print

# make sure the iterator works--find pluto
print "make sure the iterator works--find pluto"
for n in x:
    if (n.value == "pluto"):
        print "found pluto!"
        break
    else:
        print "oops pluto not found--fix this!"
