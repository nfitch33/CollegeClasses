import copy
import random

EMPTY = "."
DUCK = "D"
WHITE = "w"
BLACK = "b"

PIECE_VALUE = {"P": 1, "N": 3, "B": 3, "R": 5, "Q": 9, "K": 1000}

def starting_board():
    board = [
        ["Rb","Nb","Bb","Qb","Kb","Bb","Nb","Rb"],
        ["Pb"]*8,
        [EMPTY]*8,
        [EMPTY]*8,
        [EMPTY]*8,
        [EMPTY]*8,
        ["Pw"]*8,
        ["Rw","Nw","Bw","Qw","Kw","Bw","Nw","Rw"],
    ]
    duck_pos = (3, 3)
    return board, duck_pos

def in_bounds(r, c): return 0 <= r < 8 and 0 <= c < 8
def is_duck(r, c, duck_pos): return (r, c) == duck_pos

def generate_moves(board, duck_pos, color):
    moves = []
    for r in range(8):
        for c in range(8):
            piece = board[r][c]
            if piece != EMPTY and piece[1] == color:
                moves.extend(piece_moves(board, duck_pos, r, c, piece))
    return moves

def piece_moves(board, duck_pos, r, c, piece):
    kind, color = piece[0], piece[1]
    moves = []

    if kind == "P":
        dir = -1 if color == WHITE else 1
        nr = r + dir
        if in_bounds(nr, c) and not is_duck(nr, c, duck_pos) and board[nr][c]==EMPTY:
            moves.append(((r,c),(nr,c)))
        start = 6 if color==WHITE else 1
        if r==start:
            nr2=r+2*dir
            if in_bounds(nr2,c) and board[nr][c]==EMPTY and board[nr2][c]==EMPTY \
               and not is_duck(nr,c,duck_pos) and not is_duck(nr2,c,duck_pos):
                moves.append(((r,c),(nr2,c)))
        for dc in [-1,1]:
            nr,nc=r+dir,c+dc
            if in_bounds(nr,nc) and not is_duck(nr,nc,duck_pos):
                if board[nr][nc]!=EMPTY and board[nr][nc][1]!=color:
                    moves.append(((r,c),(nr,nc)))

    elif kind=="N":
        jumps=[(2,1),(2,-1),(-2,1),(-2,-1),(1,2),(1,-2),(-1,2),(-1,-2)]
        for dr,dc in jumps:
            nr,nc=r+dr,c+dc
            if in_bounds(nr,nc) and not is_duck(nr,nc,duck_pos):
                if board[nr][nc]==EMPTY or board[nr][nc][1]!=color:
                    moves.append(((r,c),(nr,nc)))
    elif kind in "BRQK":
        dirs=[]
        if kind in "BQ": dirs+=[(1,1),(1,-1),(-1,1),(-1,-1)]
        if kind in "RQ": dirs+=[(1,0),(-1,0),(0,1),(0,-1)]
        if kind=="K": dirs=[(1,1),(1,-1),(-1,1),(-1,-1),(1,0),(-1,0),(0,1),(0,-1)]
        for dr,dc in dirs:
            nr,nc=r+dr,c+dc
            while in_bounds(nr,nc):
                if is_duck(nr,nc,duck_pos): break
                if board[nr][nc]==EMPTY: moves.append(((r,c),(nr,nc)))
                else:
                    if board[nr][nc][1]!=color: moves.append(((r,c),(nr,nc)))
                    break
                if kind=="K": break
                nr+=dr; nc+=dc
    return moves

def make_move(board, duck_pos, move, duck_target, color, ai_promote=False):
    (r1,c1),(r2,c2)=move
    new_board=copy.deepcopy(board)
    piece=new_board[r1][c1]

    win=False
    if new_board[r2][c2]!=EMPTY and new_board[r2][c2][0]=="K" and new_board[r2][c2][1]!=color:
        win=True

    new_board[r2][c2]=piece
    new_board[r1][c1]=EMPTY

    # pawn promotion
    if piece[0]=="P" and (r2==0 or r2==7):
        promote_to=random.choice(["Q","R","B","N"]) if ai_promote else "Q"
        new_board[r2][c2]=promote_to+color

    return new_board, duck_target, win

def get_legal_duck_squares(board, duck_pos):
    return [(r,c) for r in range(8) for c in range(8) if board[r][c]==EMPTY and (r,c)!=duck_pos]
