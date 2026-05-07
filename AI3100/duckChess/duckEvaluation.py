# duckEvaluation.py
# Heuristic evaluation for Duck Chess AI

import copy

# Piece values
PIECE_VALUES = {
    "P": 1,
    "N": 3,
    "B": 3,
    "R": 5,
    "Q": 9,
    "K": 1000  # high value for king
}

# ===========================================
# Helpers
# ===========================================
def in_bounds(r, c):
    return 0 <= r < 8 and 0 <= c < 8

def is_enemy(piece, color):
    return piece != "." and piece[1] != color

def is_empty(piece):
    return piece == "."

def generate_moves(board, duck_pos, color):
    # Import the same piece_moves logic as in duckChessAI
    from duckChessAI import piece_moves
    moves = []
    for r in range(8):
        for c in range(8):
            piece = board[r][c]
            if piece.endswith(color):
                moves.extend(piece_moves(board, duck_pos, r, c, piece))
    return moves

# ===========================================
# Evaluation function
# ===========================================
def evaluate_board(board, duck_pos, color):
    """
    Evaluate board from the perspective of `color`.
    Returns positive score if good for color, negative if bad.
    """
    score = 0
    for r in range(8):
        for c in range(8):
            piece = board[r][c]
            if piece == ".": continue
            val = PIECE_VALUES.get(piece[0], 0)
            if piece[1] == color:
                score += val
            else:
                score -= val

    # Mobility: number of legal moves
    my_moves = generate_moves(board, duck_pos, color)
    opp_color = "w" if color == "b" else "b"
    opp_moves = generate_moves(board, duck_pos, opp_color)
    score += 0.1 * len(my_moves) - 0.1 * len(opp_moves)

    # Duck penalty: avoid duck blocking own pieces
    duck_r, duck_c = duck_pos
    # Penalize duck near own pawns
    for dr in range(-1,2):
        for dc in range(-1,2):
            nr, nc = duck_r+dr, duck_c+dc
            if in_bounds(nr,nc) and board[nr][nc] != ".":
                if board[nr][nc][1] == color:
                    score -= 0.2

    return score
