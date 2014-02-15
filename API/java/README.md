Important Things to Note
-------------------------
1. Inherit from class GoBot and override method onMyTurn!
2. ExampleBot.java shows you how to do this.
3. For your java bot to work with the engine, you may have to use a shell script such as RunExampleBot.sh (edit as necessary) since the GoEngine does not handle complex shell commands.

e.g.

The way that seems to work:
./GoEngine RunExampleBot.sh hedonismbot.py

Where RunExampleBot.sh contains:
	#!/usr/bin/env bash
	java ExampleBot

This will not work!
./GoEngine `java ExampleBot` hedonismbot.py
