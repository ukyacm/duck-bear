#!/usr/bin/env python

import sys, os, random, time
from bot import GoBot

class ExampleBot(GoBot):
	def onMyTurn(self,player,boardState):
		time.sleep(2)
		x = random.randint(0,9);
		y = random.randint(0,9);
		p = random.randint(0,1);
	
		return x, y, p # here is my move
	

gobot = ExampleBot()
gobot.start()
