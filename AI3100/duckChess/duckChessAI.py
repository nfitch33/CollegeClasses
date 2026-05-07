# duckChessAI.py
import copy
import random
from duckChessLogic import generate_moves, make_move, get_legal_duck_squares, PIECE_VALUE, piece_moves

# ========================================
# Piece-square / center control table
# ========================================
CENTER_WEIGHT = [
    [3, 4, 4, 5, 5, 4, 4, 3],
    [4, 6, 6, 7, 7, 6, 6, 4],
    [4, 6, 8, 8, 8, 8, 6, 4],
    [5, 7, 8, 10,10,8, 7, 5],
    [5, 7, 8, 10,10,8, 7, 5],
    [4, 6, 8, 8, 8, 8, 6, 4],
    [4, 6, 6, 7, 7, 6, 6, 4],
    [3, 4, 4, 5, 5, 4, 4, 3]
]

# ========================================
# Hybrid AI with alpha-beta pruning
# ========================================
def hybrid_ai(board, duck_pos, color):
    depth = 1

    # ========================================
    # Board evaluation
    # ========================================
    def evaluate_board(b, c):
        score = 0
        opp = "b" if c=="w" else "w"
        for r in range(8):
            for col in range(8):
                p = b[r][col]
                if p == ".":
                    continue
                val = PIECE_VALUE.get(p[0],0)
                if p[1]==c:
                    score += val
                    score += CENTER_WEIGHT[r][col]*0.1
                else:
                    score -= val
                    score -= CENTER_WEIGHT[r][col]*0.1
        # Mobility
        score += 0.1*len(generate_moves(b, duck_pos, c))
        score -= 0.1*len(generate_moves(b, duck_pos, opp))
        return score

    # ========================================
    # Move ordering
    # ========================================
    def move_priority(b, duck_p, turn):
        moves = generate_moves(b, duck_p, turn)

        def king_position(board, color):
            for r in range(8):
                for c in range(8):
                    if board[r][c] == "K"+color:
                        return r,c
            return None

        def is_square_defended(board, r, c, color):
            enemy = "b" if color=="w" else "w"
            for rr in range(8):
                for cc in range(8):
                    p = board[rr][cc]
                    if p != "." and p[1]==enemy:
                        for mv in piece_moves(board, duck_p, rr, cc, p):
                            if mv[1] == (r,c):
                                return True
            return False

        def is_king_safe_after(board, move, duck_target, color):
            new_board, new_duck, _ = make_move(board, duck_p, move, duck_target, color, ai_promote=True)
            king_r, king_c = king_position(new_board, color)
            if king_r is None:
                return False
            return not is_square_defended(new_board, king_r, king_c, color)

        def move_score(mv):
            (r1,c1),(r2,c2)=mv
            piece = b[r1][c1]
            target = b[r2][c2]
            score = 0

            # King safety
            safe = any(is_king_safe_after(b, mv, (dr,dc), turn)
                       for dr, dc in get_legal_duck_squares(b, duck_p))
            if not safe:
                return -9999

            # Capture evaluation
            if target != "." and target[1] != turn:
                score += PIECE_VALUE.get(target[0],0)*100
                if not is_square_defended(b,r2,c2,turn):
                    score += PIECE_VALUE.get(target[0],0)*50  # free capture bonus

            # Promotion
            if piece[0]=="P" and (r2==0 or r2==7):
                score += 90

            # Center control
            score += CENTER_WEIGHT[r2][c2]*2
            return score

        moves.sort(key=move_score, reverse=True)
        return moves

    # ========================================
    # Alpha-beta minimax
    # ========================================
    def minimax(b, depth, alpha, beta, turn, duck_p):
        legal = move_priority(b, duck_p, turn)
        if depth==0 or not legal:
            return evaluate_board(b, color), None, None

        if turn == color:
            max_eval = -float("inf")
            best_mv = None
            best_duck = None
            for mv in legal:
                new_board, new_duck, _ = make_move(b, duck_p, mv, duck_p, turn, ai_promote=True)
                duck_squares = get_legal_duck_squares(new_board, new_duck)
                for dr,dc in duck_squares:
                    final_board, final_duck, _ = make_move(new_board, new_duck, mv, (dr,dc), turn, ai_promote=True)
                    val,_,_ = minimax(final_board, depth-1, alpha, beta, "b" if turn=="w" else "w", final_duck)
                    if val > max_eval:
                        max_eval = val
                        best_mv = mv
                        best_duck = (dr,dc)
                    alpha = max(alpha, max_eval)
                    if beta <= alpha:
                        break
            return max_eval, best_mv, best_duck
        else:
            min_eval = float("inf")
            best_mv = None
            best_duck = None
            for mv in legal:
                new_board, new_duck, _ = make_move(b, duck_p, mv, duck_p, turn, ai_promote=True)
                duck_squares = get_legal_duck_squares(new_board, new_duck)
                for dr,dc in duck_squares:
                    final_board, final_duck, _ = make_move(new_board, new_duck, mv, (dr,dc), turn, ai_promote=True)
                    val,_,_ = minimax(final_board, depth-1, alpha, beta, "b" if turn=="w" else "w", final_duck)
                    if val < min_eval:
                        min_eval = val
                        best_mv = mv
                        best_duck = (dr,dc)
                    beta = min(beta, min_eval)
                    if beta <= alpha:
                        break
            return min_eval, best_mv, best_duck

    _, move, duck_target = minimax(board, depth, -float("inf"), float("inf"), color, duck_pos)
    return move, duck_target

def save_q_table():
    pass
