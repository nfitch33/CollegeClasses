# duckChessPvP.py
import pygame
import sys
import time
from duckChessLogic import starting_board, generate_moves, make_move
from duckChessAI import hybrid_ai, save_q_table

TILE = 80
WIDTH = HEIGHT = TILE * 8
FPS = 60

pygame.init()
win = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Duck Chess")
clock = pygame.time.Clock()

FONT = pygame.font.SysFont("arial", 52, bold=True)
END_FONT = pygame.font.SysFont("arial", 64, bold=True)

LIGHT = (200, 150, 255)
DARK = (120, 40, 180)
WHITE_PIECE = (255, 255, 255)
BLACK_PIECE = (0, 0, 0)
HIGHLIGHT_COLOR = (0, 255, 0, 120)


def draw_board(board, duck_pos, legal_moves=[], dragging_piece=None, dragging_pos=None, duck_moves=[]):
    for r in range(8):
        for c in range(8):
            color = LIGHT if (r + c) % 2 == 0 else DARK
            pygame.draw.rect(win, color, (c * TILE, r * TILE, TILE, TILE))

            # Highlight legal moves
            if (r, c) in legal_moves or (r, c) in duck_moves:
                s = pygame.Surface((TILE, TILE))
                s.set_alpha(120)
                s.fill(HIGHLIGHT_COLOR[:3])
                win.blit(s, (c * TILE, r * TILE))

            # Draw duck
            if (r, c) == duck_pos:
                text = FONT.render("D", True, (255, 220, 0))
                win.blit(text, (c * TILE + 22, r * TILE + 10))
                continue

            # Skip piece if currently dragging it
            if dragging_piece and (r, c) == dragging_piece["origin"]:
                continue

            # Draw piece
            piece = board[r][c]
            if piece != ".":
                piece_color = WHITE_PIECE if piece[1] == "w" else BLACK_PIECE
                text = FONT.render(piece[0], True, piece_color)
                win.blit(text, (c * TILE + 22, r * TILE + 10))

    # Draw dragging piece on top of everything
    if dragging_piece:
        piece_color = WHITE_PIECE if dragging_piece["piece"][1] == "w" else BLACK_PIECE
        text = FONT.render(dragging_piece["piece"][0], True, piece_color)
        win.blit(text, dragging_pos)


def get_square_from_mouse(pos):
    x, y = pos
    r = y // TILE
    c = x // TILE
    return (r, c) if 0 <= r < 8 and 0 <= c < 8 else None


def get_legal_duck_squares(board, duck_pos):
    return [(r, c) for r in range(8) for c in range(8) if board[r][c] == "." and (r, c) != duck_pos]


def choose_duck_square(board, duck_pos, legal_moves):
    while True:
        clock.tick(FPS)
        draw_board(board, duck_pos, duck_moves=legal_moves)
        pygame.display.flip()
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                save_q_table()
                sys.exit()
            if event.type == pygame.MOUSEBUTTONDOWN:
                sq = get_square_from_mouse(event.pos)
                if sq and sq in legal_moves:
                    return sq


def main():
    board, duck_pos = starting_board()
    turn = "w"
    dragging_piece = None
    dragging = False
    legal_moves = []
    temp_board = None

    while True:
        clock.tick(FPS)
        mouse_pos = pygame.mouse.get_pos()

        draw_board(
            temp_board if temp_board else board,
            duck_pos,
            legal_moves=legal_moves,
            dragging_piece=dragging_piece,
            dragging_pos=(mouse_pos[0] - 35, mouse_pos[1] - 45),
        )

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                save_q_table()
                sys.exit()

            # Start dragging a piece
            if event.type == pygame.MOUSEBUTTONDOWN and not dragging:
                sq = get_square_from_mouse(event.pos)
                if sq:
                    r, c = sq
                    piece = board[r][c]
                    if piece != "." and piece.endswith(turn):
                        dragging_piece = {"origin": (r, c), "piece": piece}
                        dragging = True
                        legal_moves = [mv[1] for mv in generate_moves(board, duck_pos, turn) if mv[0] == (r, c)]

            # Drop the piece
            if event.type == pygame.MOUSEBUTTONUP and dragging:
                dragging = False
                dest = get_square_from_mouse(event.pos)
                if dest:
                    r1, c1 = dragging_piece["origin"]
                    r2, c2 = dest
                    legal = generate_moves(board, duck_pos, turn)
                    chosen = None
                    for mv in legal:
                        if mv == ((r1, c1), (r2, c2)):
                            chosen = mv
                            break
                    if chosen:
                        temp_board = [row.copy() for row in board]
                        temp_board[r1][c1] = "."
                        temp_board[r2][c2] = dragging_piece["piece"]
                        pygame.display.flip()

                        # Duck placement
                        duck_legal = get_legal_duck_squares(temp_board, duck_pos)
                        duck_sq = choose_duck_square(temp_board, duck_pos, duck_legal)

                        # Make move and show duck immediately
                        board, duck_pos, game_over = make_move(board, duck_pos, chosen, duck_sq, turn)
                        draw_board(board, duck_pos)
                        pygame.display.flip()
                        time.sleep(0.2)  # small pause so player sees the duck

                        if game_over:
                            draw_board(board, duck_pos)
                            pygame.display.flip()
                            text = END_FONT.render(f"{'White' if turn=='w' else 'Black'} wins!", True, (255, 0, 0))
                            win.blit(text, (WIDTH // 2 - text.get_width() // 2, HEIGHT // 2 - text.get_height() // 2))
                            pygame.display.flip()
                            pygame.time.wait(3000)
                            pygame.quit()
                            save_q_table()
                            sys.exit()

                        turn = "b" if turn == "w" else "w"
                        temp_board = None

                dragging_piece = None
                legal_moves = []

        # AI turn
        if turn == "b":
            pygame.display.flip()
            pygame.time.wait(500)  # small delay to see AI move
            move, duck_target = hybrid_ai(board, duck_pos, "b")
            board, duck_pos, game_over = make_move(board, duck_pos, move, duck_target, "b")
            draw_board(board, duck_pos)
            pygame.display.flip()
            time.sleep(0.2)  # show AI move

            if game_over:
                draw_board(board, duck_pos)
                pygame.display.flip()
                text = END_FONT.render(f"Black wins!", True, (255, 0, 0))
                win.blit(text, (WIDTH // 2 - text.get_width() // 2, HEIGHT // 2 - text.get_height() // 2))
                pygame.display.flip()
                pygame.time.wait(3000)
                pygame.quit()
                save_q_table()
                sys.exit()

            turn = "w"

        pygame.display.flip()


if __name__ == "__main__":
    main()
