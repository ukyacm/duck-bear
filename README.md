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

API Transactions
[BOT1] ----------------------- [ Engine ] ----------------------- [BOT2]
   x <------ init [pnum] --------- x
                                   x -------- init [pnum] ---------> x
   x <---- request move [bs] ----- x 
   x ----- move x,y, or pass ----> x
                               [RESOLVE]
                                   x ----- request move [bs] ----> x 
                                   x <---- move x,y, or pass ----- x
                               [RESOLVE]
                                  ...
                                  ...

Web Player
- transaction: (turn number, board state, score?)

Notes:
- [pnum] is player number of bot
- [bs] is array of board as a single string of length BOARD_SIZE*BOARD_SIZE
- BOT1 is arbitrarily first to move

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

