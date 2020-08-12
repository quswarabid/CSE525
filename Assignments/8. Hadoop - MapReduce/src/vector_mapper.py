#!/usr/bin/env python
"""mapper.py"""

import sys
from array import *

M = [[11, 12, 5], [15, 6,10], [10, 8, 12]]
V = [2, 3, 4]

for i in range(len(M)):
    for j in range(len(M)):
        print("{0}\t{1}\t{2}".format(i, M[i][j], V[i]))

