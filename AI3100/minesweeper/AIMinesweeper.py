# not perfect, sometimes places '.' without filling out whole board

import random

class Minesweeper:
    def __init__(self, rows, cols, mines):
        self.rows = rows
        self.cols = cols
        self.mines = mines
        self.board = [[0]*cols for _ in range(rows)]
        self.revealed = [[False]*cols for _ in range(rows)]
        self.flags = [[False]*cols for _ in range(rows)]
        self._place_mines()
        self._calculate_numbers()

    def _place_mines(self):
        positions = [(r, c) for r in range(self.rows) for c in range(self.cols)]
        random.shuffle(positions)
        for r, c in positions[:self.mines]:
            self.board[r][c] = -1  # -1 means mine

    def _calculate_numbers(self):
        for r in range(self.rows):
            for c in range(self.cols):
                if self.board[r][c] == -1:
                    continue
                count = 0
                for dr in [-1, 0, 1]:
                    for dc in [-1, 0, 1]:
                        nr, nc = r + dr, c + dc
                        if 0 <= nr < self.rows and 0 <= nc < self.cols:
                            if self.board[nr][nc] == -1:
                                count += 1
                self.board[r][c] = count

    def print_board(self, reveal_all=False):
        # Print column headers
        print("    ", end="")
        for c in range(self.cols):
            print(f" {c}  ", end="")
        print()
        print("   +" + "---+" * self.cols)

        for r in range(self.rows):
            print(f"{r:2} |", end="")
            for c in range(self.cols):
                if reveal_all:
                    if self.board[r][c] == -1:
                        char = '*'
                    elif self.board[r][c] == 0:
                        char = ' '
                    else:
                        char = str(self.board[r][c])
                else:
                    if self.flags[r][c]:
                        char = 'F'
                    elif self.revealed[r][c]:
                        char = ' ' if self.board[r][c] == 0 else str(self.board[r][c])
                    else:
                        char = '.'
                print(f" {char} |", end="")
            print()
            print("   +" + "---+" * self.cols)


class MinesweeperSolver:
    def __init__(self, game):
        self.game = game
        self.rows = game.rows
        self.cols = game.cols
        self.board = game.board
        self.revealed = game.revealed
        self.flags = game.flags

    def neighbors(self, r, c):
        for dr in [-1, 0, 1]:
            for dc in [-1, 0, 1]:
                if dr == 0 and dc == 0:
                    continue
                nr, nc = r + dr, c + dc
                if 0 <= nr < self.rows and 0 <= nc < self.cols:
                    yield nr, nc

    def is_solved(self):
        for r in range(self.rows):
            for c in range(self.cols):
                if self.board[r][c] != -1 and not self.revealed[r][c]:
                    return False
        return True

    def reveal_cell(self, r, c):
        if self.revealed[r][c] or self.flags[r][c]:
            return
        self.revealed[r][c] = True
        if self.board[r][c] == 0:
            for nr, nc in self.neighbors(r, c):
                if not self.revealed[nr][nc]:
                    self.reveal_cell(nr, nc)

    def basic_inference(self):
        changed = False
        for r in range(self.rows):
            for c in range(self.cols):
                if not self.revealed[r][c]:
                    continue

                flagged = 0
                hidden = []
                for nr, nc in self.neighbors(r, c):
                    if self.flags[nr][nc]:
                        flagged += 1
                    elif not self.revealed[nr][nc]:
                        hidden.append((nr, nc))

                # Flag all hidden neighbors if count matches
                if self.board[r][c] == flagged + len(hidden) and len(hidden) > 0:
                    for hr, hc in hidden:
                        if not self.flags[hr][hc]:
                            self.flags[hr][hc] = True
                            changed = True

                # Reveal all hidden neighbors if flagged count matches number
                elif self.board[r][c] == flagged and len(hidden) > 0:
                    for hr, hc in hidden:
                        if not self.revealed[hr][hc] and not self.flags[hr][hc]:
                            self.reveal_cell(hr, hc)
                            changed = True
        return changed

    def advanced_inference(self):
        changed = False
        cells = []
        for r in range(self.rows):
            for c in range(self.cols):
                if not self.revealed[r][c]:
                    continue
                hidden = []
                flagged = 0
                for nr, nc in self.neighbors(r, c):
                    if self.flags[nr][nc]:
                        flagged += 1
                    elif not self.revealed[nr][nc]:
                        hidden.append((nr, nc))
                if len(hidden) > 0:
                    cells.append({
                        'pos': (r, c),
                        'number': self.board[r][c],
                        'flagged': flagged,
                        'hidden': set(hidden)
                    })

        for i in range(len(cells)):
            for j in range(len(cells)):
                if i == j:
                    continue
                c1 = cells[i]
                c2 = cells[j]

                h1 = c1['hidden']
                h2 = c2['hidden']

                if h1 and h1.issubset(h2):
                    diff = c2['number'] - c2['flagged'] - (c1['number'] - c1['flagged'])
                    diff_hidden = h2 - h1
                    if diff == len(diff_hidden) and diff > 0:
                        for cell in diff_hidden:
                            r, c = cell
                            if not self.flags[r][c]:
                                self.flags[r][c] = True
                                changed = True
                    elif diff == 0 and len(diff_hidden) > 0:
                        for cell in diff_hidden:
                            r, c = cell
                            if not self.revealed[r][c] and not self.flags[r][c]:
                                self.reveal_cell(r, c)
                                changed = True
        return changed

    def solve(self):
        # Reveal first zero cell to start
        started = False
        for r in range(self.rows):
            for c in range(self.cols):
                if self.board[r][c] == 0:
                    self.reveal_cell(r, c)
                    started = True
                    break
            if started:
                break

        # Keep applying inference repeatedly until no progress
        while True:
            changed_basic = self.basic_inference()
            changed_advanced = self.advanced_inference()
            if not (changed_basic or changed_advanced):
                break

        if self.is_solved():
            print("Solved successfully!")
        else:
            print("Solver stopped. Couldn't solve fully with logic alone.")

if __name__ == "__main__":
    rows, cols, mines = 9, 9, 10
    game = Minesweeper(rows, cols, mines)
    solver = MinesweeperSolver(game)

    print("Initial board (hidden):")
    game.print_board()

    print("\nSolving...\n")
    solver.solve()

    print("\nFinal board (revealed):")
    game.print_board(reveal_all=True)

    print("\nSolver view (flags and revealed):")
    game.print_board()
