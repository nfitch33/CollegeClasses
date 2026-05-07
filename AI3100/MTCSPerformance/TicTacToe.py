import time
import math
import random
import sys

class TicTacToe:
    def __init__(self):
        self.board = [' '] * 9
        self.current_player = 'X'  # X always starts
    
    def clone(self):
        clone = TicTacToe()
        clone.board = self.board[:]
        clone.current_player = self.current_player
        return clone
    
    def available_moves(self):
        return [i for i, v in enumerate(self.board) if v == ' ']
    
    def make_move(self, move):
        if self.board[move] != ' ':
            raise ValueError("Invalid move")
        self.board[move] = self.current_player
        self.current_player = 'O' if self.current_player == 'X' else 'X'
    
    def winner(self):
        b = self.board
        lines = [
            (0,1,2), (3,4,5), (6,7,8),  # rows
            (0,3,6), (1,4,7), (2,5,8),  # columns
            (0,4,8), (2,4,6)            # diagonals
        ]
        for i,j,k in lines:
            if b[i] == b[j] == b[k] != ' ':
                return b[i]
        if ' ' not in b:
            return 'Draw'
        return None
    
    def is_game_over(self):
        return self.winner() is not None
    
    def print_board(self):
        b = self.board
        print(f"{b[0]}|{b[1]}|{b[2]}")
        print("-+-+-")
        print(f"{b[3]}|{b[4]}|{b[5]}")
        print("-+-+-")
        print(f"{b[6]}|{b[7]}|{b[8]}")

class MCTSNode:
    def __init__(self, state, parent=None, move=None):
        self.state = state
        self.parent = parent
        self.move = move  # Move that led from parent to this node
        self.children = []
        self.wins = 0
        self.visits = 0
        self.untried_moves = state.available_moves()
        self.player_just_moved = 'O' if state.current_player == 'X' else 'X'  # player who made last move
    
    def uct_select_child(self):
        log_parent_visits = math.log(self.visits)
        def uct(child):
            return (child.wins / child.visits) + math.sqrt(2 * log_parent_visits / child.visits)
        return max(self.children, key=uct)
    
    def add_child(self, move, state):
        child = MCTSNode(state, parent=self, move=move)
        self.untried_moves.remove(move)
        self.children.append(child)
        return child
    
    def update(self, result):
        self.visits += 1
        self.wins += result

def MCTS(root_state, time_limit=1.0):
    """
    Monte-Carlo Tree Search with a time limit in seconds.

    1. Selection: traverse tree via UCT until node with untried moves or terminal.
    2. Expansion: expand one untried move.
    3. Simulation: play random moves to end.
    4. Backpropagation: update win/visit stats on path.
    """
    root_node = MCTSNode(root_state)
    end_time = time.time() + time_limit

    iteration = 0
    while time.time() < end_time:
        node = root_node
        state = root_state.clone()

        # 1. Selection
        while node.untried_moves == [] and node.children != []:
            node = node.uct_select_child()
            state.make_move(node.move)

        # 2. Expansion
        if node.untried_moves:
            move = random.choice(node.untried_moves)
            state.make_move(move)
            node = node.add_child(move, state)

        # 3. Simulation (rollout)
        while not state.is_game_over():
            moves = state.available_moves()
            state.make_move(random.choice(moves))

        # 4. Backpropagation
        winner = state.winner()
        if winner == 'Draw':
            result = 0.5
        elif winner == node.player_just_moved:
            result = 1
        else:
            result = 0

        # Propagate results up the tree
        while node is not None:
            node.update(result)
            result = 1 - result  # switch result for opponent
            node = node.parent

        iteration += 1

    print(f"MCTS iterations: {iteration}")
    print(f"Move visits: {[(c.move, c.visits) for c in root_node.children]}")
    best_child = max(root_node.children, key=lambda c: c.visits)
    return best_child.move

def find_immediate_win_or_block(game, player):
    opponent = 'O' if player == 'X' else 'X'
    # Immediate win
    for move in game.available_moves():
        clone = game.clone()
        clone.make_move(move)
        if clone.winner() == player:
            return move
    # Immediate block opponent
    for move in game.available_moves():
        clone = game.clone()
        clone.make_move(move)
        if clone.winner() == opponent:
            return move
    return None

def human_turn(game):
    while True:
        try:
            move = int(input("Your move (0-8): "))
            if move in game.available_moves():
                return move
            else:
                print("Invalid move, try again.")
        except:
            print("Please enter a number 0-8.")

def play_game():
    human_first = False
    if len(sys.argv) > 1 and sys.argv[1].lower() == "first":
        human_first = True

    game = TicTacToe()
    print("You are 'O', AI is 'X'. Positions 0-8 as:")
    print("0|1|2\n-+-+-\n3|4|5\n-+-+-\n6|7|8")
    game.print_board()

    if human_first:
        game.current_player = 'O'

    while not game.is_game_over():
        if game.current_player == 'O':
            move = human_turn(game)
            game.make_move(move)
        else:
            print("AI thinking...")
            immediate_move = find_immediate_win_or_block(game, 'X')
            if immediate_move is not None:
                move = immediate_move
            else:
                move = MCTS(game, time_limit=1)
            print(f"AI plays move: {move}")
            game.make_move(move)
        game.print_board()

    w = game.winner()
    if w == 'Draw':
        print("Game drawn!")
    else:
        print(f"Winner is {w}!")

if __name__ == "__main__":
    play_game()
