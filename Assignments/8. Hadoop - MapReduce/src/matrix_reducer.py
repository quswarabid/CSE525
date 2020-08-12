#!/usr/bin/env python
import sys
a={}
b={}
for input_line in sys.stdin:
	input_line = input_line.strip()
	
	this_key,value = input_line.split("\t",1)
	v = value.split(",")
	if this_key=='a':
		a[(int(v[1]),int(v[2]))]=int(v[3])
	elif this_key=='b':
		b[(int(v[1]),int(v[2]))]=int(v[3])
	
result=0
for i in range(0,4):  
	for j in range(0,5):  
		for k in range(0,3):  
			result = result + a[(i,k)]*b[(k,j)]  
		print("({0},{1})\t{2}".format(i,j,result))
		result =0  
     
