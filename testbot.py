#!/usr/bin/env python

import sys, os, random, time

class GoBot:
	BSIZE = 9
	player = None
	
	def start(self):
		self.sendMessage("HI!")
		msg = self.getMessage().split(' ')
		if msg[0] == "INITIALIZE":
			player = int(msg[1])
		else:
			exit("bad msg, expected init\n")
		
		self.sendMessage("READY!")
		
		while True:
			msg = self.getMessage().split(' ')
			if msg[0] == "REQUEST_MOVE":
				boardState = self.parseBoardState(msg[1])
				x, y, p = self.onMyTurn(player,boardState)
				self.sendMessage("RESPONSE_MOVE %s %s %s" % (x,y,p))
			elif msg[0] == "END_GAME":
				exit()
			else:
				exit("bad msg, expected move; got '" + msg[0] + "'\n")

	def getMessage(self):
		return sys.stdin.readline().rstrip()

	def sendMessage(self,msg):
		sys.stdout.write(msg + '\n')
		sys.stdout.flush()
		
	def parseBoardState(self,data):
		ptr = 0
		grid = []
		if len(data) != self.BSIZE*self.BSIZE:
			exit('incomplete board state array data\n')
			
		for i in range(self.BSIZE):
			row = []
			for j in range(self.BSIZE):
				row.append(data[ptr])
				ptr += 1
				
			grid.append(row)

		return grid
		
	def onMyTurn(self,player,boardState):
		time.sleep(2)
		x = random.randint(0,9);
		y = random.randint(0,9);
		p = random.randint(0,1);
	
		return x, y, p # here is my move
	

gobot = GoBot()
gobot.start()
