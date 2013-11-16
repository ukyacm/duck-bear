#!/usr/bin/env python

import sys, os, random, time
from bot import GoBot

class ExampleBot(GoBot):
	def __init__(self):
		self.anchor = None
		
	def getEdges(self,x,y):
		rtn = []
		if x-1 >= 0:
			rtn.append((x-1,y))
		if x+1 <= 8:
			rtn.append((x+1,y))
		if y+1 <= 8:
			rtn.append((x,y+1))
		if y-1 >= 0:
			rtn.append((x,y-1))
		return rtn
	
	def onMyTurn(self,player,boardState):
		time.sleep(1)
		
		mine = []
		others = []
		for i in range(9):
			for j in range(9):
				if boardState[i][j] == player:
					mine.append((i,j))
				elif boardState[i][j] != 0:
					others.append((i,j))
					
		x_out = 0
		y_out = 0
		
		while True:
			if self.anchor == None or self.anchor in others:
				x = random.randint(0,8)
				y = random.randint(0,8)
				
				while (x,y) in mine + others:
					x = random.randint(0,8)
					y = random.randint(0,8)
					
				self.anchor = (x,y)
				
			consider = self.getEdges(self.anchor[0],self.anchor[1])
			surely = [cell for cell in consider if cell not in mine+others]
			if len(surely):
				x_out, y_out = surely[0]
				break
			else:
				self.anchor = None
				
	
		return x_out, y_out, 0 # here is my move
	
gobot = ExampleBot()
gobot.start()
