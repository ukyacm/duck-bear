#!/usr/bin/env python

import sys, os, random, time
from GoBot import GoBot

class HedonismBot(GoBot):
	def __init__(self):
		self.anchor = (1,1)
		self.stage = 1
		self.jump = True
		
	def getEdges(self,x,y):
		rtn = []
		if x-1 >= 0:
			rtn.append((x-1,y))
		if y+1 <= 8:
			rtn.append((x,y+1))
		if x+1 <= 8:
			rtn.append((x+1,y))
		if y-1 >= 0:
			rtn.append((x,y-1))
		return rtn
		
	def getDiagEdges(self,x,y):
		edges = [(x-1,y-1),(x+1,y+1),(x-1,y+1),(x+1,y-1)]
		bad = []
		for edge in edges:
			ex, ey = edge
			if not (ex >= 0 and ex <= 8 and ey >= 0 and ey <= 8):
				bad.append(edge)
			
		return [cell for cell in edges if cell not in bad]
	
	def rand2D(self,x,y):
		rx = random.randint(0,8)
		ry = random.randint(0,8)
			
		return (rx,ry)
		
	def isBadAnchor(self,x,y):
		test = self.getEdges(x,y)
		match = [cell for cell in test if cell not in self.filled]
		return not len(match)
		
	def nextAnchor(self):
		found = False
		
		if self.stage == 1:
			diags = self.getDiagEdges(self.anchor[0],self.anchor[1])
			while len(diags) > 0:
				cell = diags.pop()
				if not self.isBadAnchor(cell[0],cell[1]):
					x, y = cell
					found = True
					break
		
		if not found:
			x, y = self.rand2D(self.anchor[0],self.anchor[1])
			while self.isBadAnchor(x,y):
				x, y = self.rand2D(self.anchor[0],self.anchor[1])
			
		return x, y
	
	def onMyTurn(self,player,boardState):
		time.sleep(0.01)
		
		self.mine = []
		self.others = []
			
		for i in range(9):
			for j in range(9):
				if boardState[i][j] == player:
					self.mine.append((i,j))
				elif boardState[i][j] != 0:
					self.others.append((i,j))
		
		self.filled = self.mine + self.others
		if self.stage != 2 and len(self.filled) > (9*9)/4:
			self.stage = 2
			
		x_out = 0
		y_out = 0
		
		while True:
			if self.jump:
				self.anchor = self.nextAnchor()
				self.jump = False	
				
			consider = self.getEdges(self.anchor[0],self.anchor[1])
			surely = [cell for cell in consider if cell not in self.filled]
			if len(surely):
				x_out, y_out = surely[0]
				break
			else:
				self.jump = True
				
		return x_out, y_out, 0 # here is my move
	
gobot = HedonismBot()
gobot.start()
