#!/usr/bin/env python

import sys, os, random, time

BSIZE = 7
player = None

def getMessage():
	return sys.stdin.readline().rstrip()

def sendMessage(msg):
	sys.stdout.write(msg)
	sys.stdout.flush()
	
def parseBoardState(data):
	ptr = 0
	grid = []
	for i in range(BSIZE):
		row = []
		for j in range(BSIZE):
			row.append(data[ptr])
			ptr += 1
			
		grid.append(row)

while True:
	# read msg
	msg = getMessage().split(' ')
	if msg[0] == "INIT":
		player = int(msg[1])
	elif msg[0] == "REQUESTMOVE":
		boardstate = parseBoardState(msg[1])
		x, y = onMyTurn(player,boardState)
		sendMessage("MOVE %s %s" % (x,y))

def onMyTurn():
	
	# do some thinking
	
	return x, y # here is my move
	
	
