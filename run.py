import subprocess

c = ["bots/donbot/donbot", "bots/mcts/MCTSBot"]

subprocess.call(["./GoEngine", c[0], c[1]])
subprocess.call(["./GoEngine", c[0], c[1]])
subprocess.call(["./GoEngine", c[0], c[1]])
subprocess.call(["./GoEngine", c[1], c[0]])
subprocess.call(["./GoEngine", c[1], c[0]])
subprocess.call(["./GoEngine", c[1], c[0]])
