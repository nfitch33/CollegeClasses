def is_safe_global(board, row, col, n):
    # Check all directions for attacking queens
    
    # Check row and column
    for i in range(n):
        if board[row][i] == 'Q':  # same row
            if i != col:
                return False
        if board[i][col] == 'Q':  # same column
            if i != row:
                return False
    
    # Check diagonals
    for i in range(n):
        for j in range(n):
            if board[i][j] == 'Q':
                if abs(row - i) == abs(col - j) and (row != i and col != j):
                    return False
    return True

def max_queens_backtrack_global(board, n, pos, count, max_info):
    if pos == n * n:
        if count > max_info[0]:
            max_info[0] = count
            max_info[1] = [r[:] for r in board]
        return
    
    row = pos // n
    col = pos % n
    
    # Option 1: Place queen here if safe
    if is_safe_global(board, row, col, n):
        board[row][col] = 'Q'
        max_queens_backtrack_global(board, n, pos + 1, count + 1, max_info)
        board[row][col] = '*'
    # Option 2: Skip this position
    max_queens_backtrack_global(board, n, pos + 1, count, max_info)

def place_max_queens_small_n(n):
    board = [['*' for _ in range(n)] for _ in range(n)]
    max_info = [0, None]  # max count, best board
    max_queens_backtrack_global(board, n, 0, 0, max_info)
    for row in max_info[1]:
        print(''.join(row))

def solve_n_queens(n):
    # Use classical column-wise approach for n >= 4
    def is_safe_colwise(board, row, col, n):
        for i in range(col):
            if board[row][i] == 'Q':
                return False
        for i,j in zip(range(row-1,-1,-1), range(col-1,-1,-1)):
            if board[i][j] == 'Q':
                return False
        for i,j in zip(range(row+1,n), range(col-1,-1,-1)):
            if board[i][j] == 'Q':
                return False
        return True

    def solve_colwise(board, col, n):
        if col == n:
            return True
        for i in range(n):
            if is_safe_colwise(board, i, col, n):
                board[i][col] = 'Q'
                if solve_colwise(board, col + 1, n):
                    return True
                board[i][col] = '*'
        return False
    
    board = [['*' for _ in range(n)] for _ in range(n)]
    if not solve_colwise(board, 0, n):
        print("No full solution exists.")
    else:
        for row in board:
            print(''.join(row))

if __name__ == "__main__":
    n = int(input())
    if n >= 4:
        solve_n_queens(n)
    elif n >= 1:
        place_max_queens_small_n(n)
    else:
        print("n must be >= 1")
