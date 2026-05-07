import random

def print_board(board):
    print("    " + "   ".join(str(i) for i in range(9)))
    print("  +" + "---+"*9)
    for i in range(9):
        if i % 3 == 0 and i != 0:
            print("  +" + "---+"*9)
        row_str = f"{i} |"
        for j in range(9):
            val = board[i][j]
            cell = str(val) if val != 0 else " "
            row_str += f" {cell} |"
        print(row_str)
        print("  +" + "---+"*9)

def find_empty(board):
    for i in range(9):
        for j in range(9):
            if board[i][j] == 0:
                return (i, j)
    return None

def is_valid(board, num, pos):
    row, col = pos
    for j in range(9):
        if board[row][j] == num and j != col:
            return False
    for i in range(9):
        if board[i][col] == num and i != row:
            return False
    box_x = col // 3
    box_y = row // 3
    for i in range(box_y * 3, box_y * 3 + 3):
        for j in range(box_x * 3, box_x * 3 + 3):
            if board[i][j] == num and (i, j) != pos:
                return False
    return True

def solve(board):
    empty = find_empty(board)
    if not empty:
        return True
    row, col = empty
    for num in range(1, 10):
        if is_valid(board, num, (row, col)):
            board[row][col] = num
            if solve(board):
                return True
            board[row][col] = 0
    return False

def fill_board(board):
    numbers = list(range(1, 10))
    for i in range(9):
        for j in range(9):
            if board[i][j] == 0:
                random.shuffle(numbers)
                for num in numbers:
                    if is_valid(board, num, (i, j)):
                        board[i][j] = num
                        if fill_board(board):
                            return True
                        board[i][j] = 0
                return False
    return True

def remove_cells(board, holes=40):
    count = 0
    while count < holes:
        i = random.randint(0, 8)
        j = random.randint(0, 8)
        if board[i][j] != 0:
            board[i][j] = 0
            count += 1

def player_move(board, solution):
    while True:
        print_board(board)
        inp = input("Enter your move as row col num (e.g. 0 1 5), or 'q' to quit: ").strip()
        if inp.lower() == 'q':
            print("Game quit.")
            return False
        parts = inp.split()
        if len(parts) != 3 or not all(part.isdigit() for part in parts):
            print("Invalid input format.")
            continue
        row, col, num = map(int, parts)
        if not (0 <= row < 9 and 0 <= col < 9 and 1 <= num <= 9):
            print("Numbers out of range.")
            continue
        if solution[row][col] != num:
            print("Wrong number, try again.")
            continue
        if board[row][col] != 0:
            print("Cell already filled.")
            continue
        board[row][col] = num
        if all(board[i][j] != 0 for i in range(9) for j in range(9)):
            print_board(board)
            print("Congratulations! You solved the Sudoku.")
            return False

def main():
    board = [[0]*9 for _ in range(9)]
    fill_board(board)
    solution = [row[:] for row in board]
    remove_cells(board, holes=40)
    print("Welcome to Sudoku! Fill in the empty cells.")
    player_move(board, solution)

if __name__ == "__main__":
    main()
