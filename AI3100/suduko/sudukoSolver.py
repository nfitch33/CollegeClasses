def print_board(board):
    for i in range(9):
        if i % 3 == 0 and i != 0:
            print("-" * 21)
        for j in range(9):
            if j % 3 == 0 and j != 0:
                print("|", end=" ")
            print(board[i][j] if board[i][j] != 0 else ".", end=" ")
        print()

def find_empty(board):
    for i in range(9):
        for j in range(9):
            if board[i][j] == 0:
                return (i, j)  # row, col
    return None

def is_valid(board, num, pos):
    row, col = pos
    # Check row
    for j in range(9):
        if board[row][j] == num and j != col:
            return False
    # Check column
    for i in range(9):
        if board[i][col] == num and i != row:
            return False
    # Check 3x3 box
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
        return True  # Solved!
    row, col = empty
    for num in range(1, 10):
        if is_valid(board, num, (row, col)):
            board[row][col] = num
            if solve(board):
                return True
            board[row][col] = 0  # Backtrack
    return False

def get_board_from_user():
    print("Enter the Sudoku board, 9 lines with 9 digits each (use 0 for empty cells).")
    board = []
    for i in range(9):
        while True:
            row_input = input(f"Row {i+1}: ").strip()
            row_input = row_input.replace(" ", "")  # remove spaces if any
            if len(row_input) != 9 or not row_input.isdigit():
                print("Invalid input. Please enter exactly 9 digits (0-9).")
                continue
            row = [int(ch) for ch in row_input]
            board.append(row)
            break
    return board

if __name__ == "__main__":
    sudoku_board = get_board_from_user()
    print("\nSudoku puzzle you entered:")
    print_board(sudoku_board)

    if solve(sudoku_board):
        print("\nSolved Sudoku:")
        print_board(sudoku_board)
    else:
        print("No solution exists.")
