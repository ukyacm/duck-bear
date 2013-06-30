#!/usr/bin/env python

import sys, os, random, time 

sec = [3,8,2,4]
i = 0
while True:
	a = sys.stdin.readline().rstrip()

	sys.stdout.write("hello this is child ["+a+"]\n")
	sys.stdout.flush()
		
	i += 1
	if i == len(sec):
		i = 0
