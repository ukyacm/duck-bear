duck-bear
=========

Its a secret to everyone.

Engine
- rule processing
- transmit entire board states
- handle timeout
- read settings file
- take 1-move input and validate
- returns illegal move exception
- 3 strike
- start + load 2 bots
- keep previous two board state

Exceptions
Board::place(x,y) throws IllegalMoveException
	- specifically: 
	- out of bound (before resolve)
	- occupied	(before resolve)
	- return to previous state (after resolve)
	- suicide	(after resolve)

API
- languages: C++, Java, Python
- can pass
- parse board state into data structure
- function to return output to engine
- single transactions

Viewer
- move by move
- back/forward button
- current capture highlighted

