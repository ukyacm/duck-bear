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

API
- languages: C++, Java, Python
- parse board state into data structure
- function to return output to engine
- single transactions

Viewer
- move by move
- back/forward button
- current capture highlighted

Process of events:
- Engine creates two sub-processes, connects a pipe to each, sends "BEGIN" signal
- Each bot takes the "BEGIN" signal along with the board size and their player number,
  returns "OK"
- Play commences, engine quries each bot in turn, sends entire board state 
- Player sends either single move in [x,y], or [PASS]/[RESIGN]
- Engine verifies move, checks for end state, queries next player
- Play continues until end state is reached
- If bad move is sent to Engine, engine marks it as a [PASS] and gives that player a strike
- 3 strikes and the player forfits

Rule verification:
- Move is not already taken
- Move does not replicate the board from the last 2 states
- Move does not result in an immediate suicide

Resolve move
- Remove any pieces that need it, increment opposing player's score accordingly

Possible End states:
- 3 consecutive PASS moves (must be from both players, error PASSes count)
- A player has accumulated 3 error strikes
- A player has said RESIGN

Final Score Tally
- Simple score, any white space bordered by only one color goes to that color
- If a white space is bordered by two colors, stays neutral
- Black player wins in case of ties
- Also counts any captured pieces