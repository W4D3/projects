# pa1.py
# Mitchell Wade
# Sep. 1, 2015
#
# This program reads line from stdin, sorts the contents 
# of the file by based on its hostname, and prints each 
# line accordingly in its proper color.

import sys
import re

# Read through the entire file
for line in sys.stdin:
    
##### RED #####
# if hostname is "mgmt" its an infrastructure machine
    m = re.search("([0-9][0-9][0-9][0-9]-[0-9][0-9]-[0-9][0-9].[0-9][0-9].[0-9][0-9].[0-9][0-9]..mgmt).+", line)
    if m:
        print('\x1b[31m' + m.group() + '\x1b[39m')

##### BLUE #####
# if hostname is "notnsa" followed by three numbers it
# is a top client
    m = re.search("([0-9][0-9][0-9][0-9]-[0-9][0-9]-[0-9][0-9].[0-9][0-9].[0-9][0-9].[0-9][0-9]..notnsa[0-9][0-9][0-9]).+", line)
    if m:
        print('\x1b[34m' + m.group() + '\x1b[39m')

##### MAGENTA #####
# if hostname is a phonenumber of their deparment
# how to enumerate all numbers ###-###-####?
    m = re.search("([0-9][0-9][0-9][0-9]-[0-9][0-9]-[0-9][0-9].[0-9][0-9].[0-9][0-9].[0-9][0-9]..[0-9][0-9][0-9]-[0-9][0-9][0-9]-[0-9][0-9][0-9][0-9]).+", line)
    if m:
        print('\x1b[35m' + m.group() + '\x1b[39m')

##### GREEN #####
# if hostname is "dev", "mail", "db", "web", "app",
# or "srv" followed by four decimal digits
    m = re.search("([0-9][0-9][0-9][0-9]-[0-9][0-9]-[0-9][0-9].[0-9][0-9].[0-9][0-9].[0-9][0-9]..(dev|mail|db|web|app|srv)[0-9][0-9][0-9][0-9]).+", line)
    if m:
        print('\x1b[32m' + m.group() + '\x1b[39m')

###### YELLOW #####
# if hostname is the last five alpha-numeric characaters
# off of the machine's serial number, added a dash after
# it, and added one of the words from the GREEN category
    m = re.search("([0-9][0-9][0-9][0-9]-[0-9][0-9]-[0-9][0-9].[0-9][0-9].[0-9][0-9].[0-9][0-9]..[a-zA-Z0-9_][a-zA-Z0-9_][a-zA-Z0-9_][a-zA-Z0-9_][^mgmt]-(dev|mail|db|web|app)[^mgmt]).+", line)
    if m:
        print('\x1b[33m' + m.group() + '\x1b[39m')

##### CYAN #####
# if hostname is four hexadecimal digits, followed by a
# dash, four alphabetic characters, another dash, one 
# of the words from the GREEN category, and finally a
# single digit.
    m = re.search("([0-9][0-9][0-9][0-9]-[0-9][0-9]-[0-9][0-9].[0-9][0-9].[0-9][0-9].[0-9][0-9]..[0-9A-Fa-f][0-9A-Fa-f][0-9A-Fa-f][0-9A-Fa-f]-[A-Za-z][A-Za-z][A-Za-z][A-Za-z]-(dev|mail|db|web|app|srv)[0-9]).+", line)
    if m:
        print('\x1b[36m' + m.group() + '\x1b[39m')
