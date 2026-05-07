# trainDuckAI.py
from duckChessAI import starting_board, hybrid_ai, make_move, encode_state, update_q_table, save_q_table

NUM_GAMES = 2000

for g in range(NUM_GAMES):
    board, duck_pos = starting_board()
    turn = "w"
    history=[]
    while True:
        move,duck_target=hybrid_ai(board, duck_pos, turn)
        board, duck_pos, win=make_move(board, duck_pos, move, duck_target, turn, ai_promote=True)
        state = encode_state(board, duck_pos, turn)
        history.append((state,(move[0],move[1],duck_target),turn))
        if win:
            for s,a,t in history:
                reward=1 if t==turn else -1
                next_state=state
                update_q_table(s,a,reward,next_state)
            break
        turn="b" if turn=="w" else "w"
save_q_table()
print("Training complete. Q-table saved.")
