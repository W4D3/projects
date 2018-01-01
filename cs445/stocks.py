import sys
import re
import feedparser

from urllib import urlopen

url = "http://www.cramers-mad-money.com/feed/"
raw = urlopen(url).read()
#print raw
feed = feedparser.parse(url)
