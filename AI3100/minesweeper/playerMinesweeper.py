import random

class Minesweeper:
    def __init__(self, rows, cols, num_mines):
        self.rows = rows
        self.cols = cols
        self.num_mines = num_mines
        self.board = [[' ' for _ in range(cols)] for _ in range(rows)]
        self.visible = [['_' for _ in range(cols)] for _ in range(rows)]
        self.mines = set()
        self.game_over = False
        self.generate_mines()
        self.calculate_hints()

    def generate_mines(self):
        while len(self.mines) < self.num_mines:
            r = random.randint(0, self.rows - 1)
            c = random.randint(0, self.cols - 1)
            self.mines.add((r, c))
            self.board[r][c] = '*'

    def calculate_hints(self):
        for r in range(self.rows):
            for c in range(self.cols):
                if self.board[r][c] == '*':
                    continue
                count = sum((nr, nc) in self.mines for nr in range(r - 1, r + 2)
                            for nc in range(c - 1, c + 2)
                            if 0 <= nr < self.rows and 0 <= nc < self.cols)
                self.board[r][c] = str(count) if count > 0 else ' '

    def print_board(self):
        print("\n     " + '   '.join(f"{c}" for c in range(self.cols)))
        print("   +" + "---+" * self.cols)
        for r in range(self.rows):
            row_cells = ' | '.join(self.visible[r][c] for c in range(self.cols))
            print(f"{r:2} | {row_cells} |")
            print("   +" + "---+" * self.cols)

    def uncover(self, r, c):
        if (r, c) in self.mines:
            self.visible[r][c] = '*'
            self.game_over = True
            print("💥 Boom! You hit a mine.")
            self.reveal_all()
            return

        self._flood_fill(r, c)

        if self.check_win():
            print("🎉 Congratulations! You cleared the minefield!")
            self.reveal_all()
            self.game_over = True

    def flag(self, r, c):
        if self.visible[r][c] == '_':
            self.visible[r][c] = 'F'
        elif self.visible[r][c] == 'F':
            self.visible[r][c] = '_'

    def _flood_fill(self, r, c):
        if not (0 <= r < self.rows and 0 <= c < self.cols):
            return
        if self.visible[r][c] != '_':
            return
        self.visible[r][c] = self.board[r][c]
        if self.board[r][c] == ' ':
            for dr in [-1, 0, 1]:
                for dc in [-1, 0, 1]:
                    if dr != 0 or dc != 0:
                        self._flood_fill(r + dr, c + dc)

    def reveal_all(self):
        for r in range(self.rows):
            for c in range(self.cols):
                self.visible[r][c] = self.board[r][c]
        self.print_board()

    def check_win(self):
        for r in range(self.rows):
            for c in range(self.cols):
                if self.visible[r][c] == '_' and self.board[r][c] != '*':
                    return False
        return True

def main():
    game = Minesweeper(rows=8, cols=8, num_mines=10)

    while not game.game_over:
        game.print_board()
        move = input("Enter your move (e.g. 'u 3 4' to uncover, 'f 3 4' to flag): ").strip().lower()
        if not move:
            continue
        parts = move.split()
        if len(parts) != 3:
            print("Invalid input.")
            continue
        action, r, c = parts
        if not (r.isdigit() and c.isdigit()):
            print("Coordinates must be integers.")
            continue
        r, c = int(r), int(c)
        if not (0 <= r < game.rows and 0 <= c < game.cols):
            print("Invalid coordinates.")
            continue

        if action == 'u':
            game.uncover(r, c)
        elif action == 'f':
            game.flag(r, c)
        else:
            print("Unknown action. Use 'u' to uncover or 'f' to flag.")

if __name__ == "__main__":
    main()
