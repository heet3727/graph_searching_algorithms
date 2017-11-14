# graph_searching_algorithms

This is an implementation of 3 of the basic tree and graph searching algorithms listed below.
- Breadth-First Search (BFS)
- Depth-First Search (DFS)
- Simulated Annealing (SA)

## Specific problem for implementation
To implement these algorithms, I have taken a specific variant of n-queens problem. <br />
Given an n × n chess board with p pawns already placed with their particular positions and m queens, so that the m queens can be set up on the board in such a way that no two queens attack each other. We are supposed to check whether any arrangement for given constraint is possible or not. If there exists any arrangement then return True with possible arrangement else return False.

## Input specifications
The main file reads input file as described below:

First line: instruction of which algorithm you wanna run: BFS, DFS or SA <br />
Second line: positive 32-bit integer n, the width and height of the chess board <br />
Third line: positive 32-bit integer p, the number of pawns <br />
Next n lines: the n x n chess board, one file line per chess board row (to show you where the pawns are) <br />
It will have a 0 where there is nothing, and a 2 where there is a pawn. <br />
