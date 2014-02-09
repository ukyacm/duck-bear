#!/usr/bin/env python

import sys, os, random, time
from GoBot import GoBot

class ExampleBot(GoBot):
	def onMyTurn(self,player,boardState):
		time.sleep(1)
	
		x = random.randint(0,8)
		y = random.randint(0,8)
		
		while boardState[x][y] != 0:
			x = random.randint(0,8)
			y = random.randint(0,8)
			
		p = random.randint(0,94);
			
		if p != 3:
			p = 0
		else:
			p = 1
	
		return x, y, p # here is my move
	
gobot = ExampleBot()
gobot.start()
