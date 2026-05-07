"""
AI3100 Homework 1
 - Nathaniel Fitch

This program is for a 3x3 slider puzzle. Where we have 8 numbers and 1 empty space. 
Our goal is to have a start state such as:
    1 2 3
    4 8 5
    7 x 6
Then get a goal state of:
    1 2 3
    4 5 6
    7 8 x
In the least number of moves. Example of an output will be:
    d l u r  
    d = down, l = left, u = up, r = right  

Input and Output will be standard using "cin" (C++) <-- figure out python equivalent
Output should output either a correct solution as written above or "Unsolvable" if it can't be solved.
"""

'''
We will need the following functions: 
BFS, Solvable?, main

We will also need, edge cases
Ex. 0=index (1) can't move up or left in our example.

We will also need a way of storing where numbers are located
Index 0-8 for 9 slots... moves will be
    u - 3   ,,   d + 3
    l - 1   ,,   r + 1

Best to use breadth first search as its not a large sample space and will look for all paths equally. 
Another option is A* but that requires more complex code and A* is much better with larger sample space.


Keep in mind, the final solution is moving x to the correct positions
ex.
123    123
456    456     Answer will be l   ... So we write inverse moves  Ex. r -> l  and d -> u
7x8    78x

Running program, use in terminal : 
    python3 sliderPuzzle.py
then either 
a.  (Your puzzle)   ex. 12345678x   then enter twice
or
b.  (Your puzzle)   ex. 123
                        456
                        78x
'''


from collections import deque
import sys

def read_input():
    puzzle = ''
    for _ in range(3):
        line = sys.stdin.readline().strip()
        puzzle += line
    return puzzle

def is_solvable(puzzle):
    tiles = [c for c in puzzle if c != 'x']
    inversions = 0
    for i in range(len(tiles)):
        for j in range(i + 1, len(tiles)):
            if tiles[i] > tiles[j]:
                inversions += 1
    return inversions % 2 == 0

def bfs(start):
    goal = '12345678x'
    moves = {
        'u': -3,
        'd': 3,
        'l': -1,
        'r': 1
    }
    # For printing the inverse move
    inverse_moves = {'u': 'd', 'd': 'u', 'l': 'r', 'r': 'l'}

    neighbors = {
        0: ['d', 'r'],
        1: ['d', 'l', 'r'],
        2: ['d', 'l'],
        3: ['u', 'd', 'r'],
        4: ['u', 'd', 'l', 'r'],
        5: ['u', 'd', 'l'],
        6: ['u', 'r'],
        7: ['u', 'l', 'r'],
        8: ['u', 'l']
    }

    visited = set()
    queue = deque()
    queue.append((start, ''))
    visited.add(start)

    while queue:
        state, path = queue.popleft()
        if state == goal:
            # Return inverted directions
            return ''.join(inverse_moves[move] for move in path)

        idx = state.index('x')
        for move in neighbors[idx]:
            new_idx = idx + moves[move]
            if 0 <= new_idx < 9:
                if move == 'l' and idx % 3 == 0:
                    continue
                if move == 'r' and idx % 3 == 2:
                    continue
                new_state = list(state)
                new_state[idx], new_state[new_idx] = new_state[new_idx], new_state[idx]
                new_state_str = ''.join(new_state)
                if new_state_str not in visited:
                    visited.add(new_state_str)
                    queue.append((new_state_str, path + move))
    return "unsolvable"

def main():
    start = read_input()
    if not is_solvable(start):
        print("unsolvable")
    else:
        result = bfs(start)
        print(result)

if __name__ == '__main__':
    main()