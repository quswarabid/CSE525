#!/usr/bin/env python
"""reducer.py"""

from operator import itemgetter
import sys

current_key   = None
current_count = 0
key           = None

for line in sys.stdin:
    line = line.strip()
    key, value1, value2 = line.split('\t', 2)

    key    = int(key)
    value1 = int(value1)
    value2 = int(value2)

    if current_key == key:
        current_count += value1 * value2
    else:
        if current_count:
            print ('X[%s]\t%s' % (current_key, current_count))
            current_count = 0
        current_count += value1 * value2
        current_key = key

if current_key == key:
    print ('X[%s]\t%s' % (current_key, current_count))

