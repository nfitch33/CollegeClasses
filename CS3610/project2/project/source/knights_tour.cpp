#include <iostream>
#include <iomanip>
#include "knights_tour.h"
using namespace std;

KnightsTour::KnightsTour(int board_size) {
  this->board_size = board_size;

  this->board.resize(board_size);
  for (int i = 0; i < board_size; ++i) {
    this->board[i].resize(board_size);
  }
}

void KnightsTour::print() {
  for (int i = 0; i < this->board_size; i++) {
    for (int j = 0; j < this->board_size; j++)
      cout << setw(4) << this->board[i][j] << " ";
    cout << endl;
  }
  cout << endl << endl;
}

// Function: get_moves()
//    Desc: Get the row and column indices of all valid
//          knight moves reachable from position row, col.
//          An invalid move would be one that sends the
//          knight off the edge of the board or
//          to a position that has already been visited.
//          
//    int row         - Current row position of knight.
//    int col         - Current column position of knight.
//    int row_moves[] - Array to store row indices
//                      of all valid new moves reachable from
//                      the current position row, col.
//    int col_moves[] - Array to store column indices
//                      of all valid new moves reachable from
//                      the current position row, col.
//    int num_moves -   Number of valid moves found. Corresponds
//                      to the sizes of row_moves and col_moves.

void KnightsTour::get_moves(int row, int col, int row_moves[], int col_moves[], int& num_moves){
  // clockwise order:
  // row: -2 -1 +1 +2 +2 +1 -1 -2
  // col: +1 +2 +2 +1 -1 -2 -2 -1
  int rows[] = {-2, -1, 1, 2, 2, 1, -1, -2};
  int cols[] = {1, 2, 2, 1, -1, -2, -2, -1};

  num_moves = 0;

  //clockwise
  for (size_t i = 0; i < 8; i++) {
    // check if the move is in bounds
    if (0 <= row + rows[i] && row + rows[i] < board_size){
      if(0 <= col + cols[i] && col + cols[i] < board_size) {
        // check if the spot is empty
        if (board.at(row + rows[i]).at(col + cols[i]) == 0) {
          //add move to rows and columns arrays
          row_moves[num_moves] = row + rows[i];
          col_moves[num_moves] = col + cols[i];
          num_moves++;
        }
      }
    }
  }
}

// Function: move() --> Recursive
//     int row        - Current row position of knight.
//     int col        - Current column position of knight.
//     int& m         - Current move id in tour.
//                      Stored in board at position
//                      row, col.
//     int& num_tours - Total number of tours found.

void KnightsTour::move(int row, int col, int& m, int& num_tours) {
  // increment m
  m++;
  // place the knight
  board.at(row).at(col) = m;
  // check if board is full
  if (m == board_size*board_size) {
    num_tours++;
    print(); // print moves
    board.at(row).at(col) = 0;
    return;  
  }

  int rows[8];
  int cols[8];
  int x = 0;

  // find all next moves
  get_moves(row, col, rows, cols, x);
 
  for (size_t i = 0; i < x; i++) {
    move(rows[i], cols[i], m, num_tours);
    m--; 
  }

  // clear current spot
  board.at(row).at(col) = 0;
}

int KnightsTour::generate(int row, int col) {
  int m = 0;
  int num_tours = 0;
  move(row, col, m, num_tours);

  return num_tours;
}
