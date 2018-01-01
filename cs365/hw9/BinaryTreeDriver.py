from tree import BinaryTree
import sys

def stringCompare(x, y):
  if x < y:
    return -1
  elif x > y: 
    return 1
  else:
    return 0

def getLine():
  if (sys.argv[1] == "-"):
    line = raw_input("CMD> ")
  else:
    line = file.readline()
    line = line.strip()
  return line

if (len(sys.argv) != 2):
  print "usage: python BinaryTreeDriver.py [- | filename]"
  sys.exit()

testTree = BinaryTree(stringCompare)

if (sys.argv[1] != "-"):
  file = open(sys.argv[1])

line = getLine()
while (line != "QUIT"):
  fields = line.split()
  if len(fields) > 0:
      if fields[0] == "INSERT":
          if (len(fields) != 2):
              print "usage: INSERT key"
          else:
              testTree.insert(fields[1])
      elif fields[0] == "FIND":
          if (len(fields) != 2):
              print "usage: FIND key"
          else:
              print testTree.find(fields[1])
      elif fields[0] == "PRINT":
          for key in testTree.traverse():
              print key
      else:
          print "usage: FIND key | INSERT key | PRINT | QUIT"
  line = getLine()
  
