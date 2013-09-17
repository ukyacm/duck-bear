#!/usr/bin/env python

import sys, os, random, time

class GoBot:
	BSIZE = 9
	player = None
	
	def start(self):
		sendMessage("HI!")
		msg = getMessage().split(' ')
		if msg[0] == "INITIALIZE":
			player = int(msg[1])
		else
			exit("bad msg, expected init")
		
		sendMessage("READY!")
		
		while True:
			msg = getMessage().split(' ')
			if msg[0] == "REQUEST_MOVE":
				boardstate = parseBoardState(msg[1])
				x, y, p = onMyTurn(player,boardState)
				sendMessage("RESPONSE_MOVE %s %s %s" % (x,y,p))
			else
				exit("bad msg, expected move req")

	def getMessage(self):
		return sys.stdin.readline().rstrip()

	def sendMessage(self,msg):
		sys.stdout.write(msg)
		sys.stdout.flush()
		
	def parseBoardState(self,data):
		ptr = 0
		grid = []
		for i in range(BSIZE):
			row = []
			for j in range(BSIZE):
				row.append(data[ptr])
				ptr += 1
				
			grid.append(row)

		return grid
		
	def onMyTurn(self):
		
		# do some thinking
	
		return x, y, p # here is my move
	

gobot = GoBotAPI()
gobot.start()
