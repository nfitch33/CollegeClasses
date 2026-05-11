/**
 * @file othello.cpp
 * @author Taylor Bruening
 * @brief implementation file for Othello class
 */
#include "othello.hpp"
#include "colors.hpp"
#include "game.hpp"
#include "piece.hpp"
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

/* COMPUTE MOVES */
void Othello::compute_moves(std::queue<std::string> &moves) const {
  string tmp = "  ";
  int i = 5;
  int j = 4;

  for (int j = 0; j < 8; j++) {
    for (int i = 0; i < 8; i++) {
      tmp[0] = char('A' + i);
      tmp[1] = char('1' + j);
      if (is_legal(tmp)) {
        moves.push(tmp);
      }
    }
  }

  if (moves.empty() == true) {
    moves.push("xx");
  }
}

/* CLONE */
main_savitch_14::game *Othello::clone() const { return new Othello(*this); }

/* EVALUATE */
int Othello::evaluate() const {
  int black_counter = 0;
  int white_counter = 0;

  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if (board[i][j].has_piece_color() == "black") {
        black_counter++;
      } else if (board[i][j].has_piece_color() == "white") {
        white_counter++;
      }
    }
  }
  int x = -1;
  int y = 1;
  int z = 0;

  if ((moves_completed() % 2 == 0) && (black_counter > white_counter)) {
    return x;
  } else if (black_counter == white_counter) {
    return z;
  } else {
    return y;
  }
}

/* IS_GAME_OVER */
bool Othello::is_game_over() const {
  int empty_counter = 0;
  int white_counter = 0;
  int black_counter = 0;
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if (board[i][j].has_piece_color() == "empty") {
        empty_counter++;
      }
      if (board[i][j].has_piece_color() == "black") {
        black_counter++;
      } else if (board[i][j].has_piece_color() == "white") {
        white_counter++;
      }
    }
  }
  if ((empty_counter != 0) && (white_counter != 0) && (black_counter != 0)) {
    return false;
  } else {
    return true;
  }
}

/* DISPLAY STATUS */
void Othello::display_status() const {
  int i = 0;
  int j = 0;
  cout << "  A  B  C  D  E  F  G  H" << endl;
  while (j < 8) {
    cout << j + 1;
    if (j % 2 == 0) {
      while (i < 8) {
        if ((board[i][j].has_piece_color()) == "black") {
          if (board[i][j].emptiness()) {
            cout << B_GREEN << "   ";
          } else {
            cout << B_GREEN << " x ";
          }
          //cout << B_GREEN << BLACK << board[i][j].holder();
          i++;
        } else if ((board[i][j].has_piece_color()) == "white") {
          if (board[i][j].emptiness()) {
            cout << B_GREEN << "   ";
          } else {
            cout << B_GREEN << " o ";
          }
          //cout << B_GREEN << WHITE << board[i][j].holder();
          i++;
        } else {
          if (board[i][j].emptiness()) {
            cout << B_GREEN << "   ";
          } else {
            cout << B_GREEN << "   ";
          }
          //cout << B_GREEN << board[i][j].holder();
          i++;
        }
        if ((board[i][j].has_piece_color()) == "black") {
          if (board[i][j].emptiness()) {
            cout << B_YELLOW << "   ";
          } else {
            cout << B_YELLOW << " x ";
          }
          //cout << B_YELLOW << BLACK << board[i][j].holder();
          i++;
        } else if ((board[i][j].has_piece_color()) == "white") {
          if (board[i][j].emptiness()) {
            cout << B_YELLOW << "   ";
          } else {
            cout << B_YELLOW << " o ";
          }
          //cout << B_YELLOW << WHITE << board[i][j].holder();
          i++;
        } else {
          if (board[i][j].emptiness()) {
            cout << B_YELLOW << "   ";
          } else {
            cout << B_YELLOW << "   ";
          }
          //cout << B_YELLOW << board[i][j].holder();
          i++;
        }
      }
    }
    if (j % 2 != 0) {
      while (i < 8) {
        if ((board[i][j].has_piece_color()) == "black") {
          if (board[i][j].emptiness()) {
            cout << B_YELLOW << "   ";
          } else {
            cout << B_YELLOW << " x ";
          }
          //cout << B_YELLOW << BLACK << board[i][j].holder();
          i++;
        } else if ((board[i][j].has_piece_color()) == "white") {
          if (board[i][j].emptiness()) {
            cout << B_YELLOW << "   ";
          } else {
            cout << B_YELLOW << " o ";
          }
          //cout << B_YELLOW << WHITE << board[i][j].holder();
          i++;
        } else {
          if (board[i][j].emptiness()) {
            cout << B_YELLOW << "   ";
          } else {
            cout << B_YELLOW << "   ";
          }
          //cout << B_YELLOW << board[i][j].holder();
          i++;
        }
        if ((board[i][j].has_piece_color()) == "black") {
          if (board[i][j].emptiness()) {
            cout << B_GREEN << "   ";
          } else {
            cout << B_GREEN << " x ";
          }
          //cout << B_GREEN << BLACK << board[i][j].holder();
          i++;
        } else if ((board[i][j].has_piece_color()) == "white") {
          if (board[i][j].emptiness()) {
            cout << B_GREEN << "   ";
          } else {
            cout << B_GREEN << " o ";
          }
          //cout << B_GREEN << WHITE << board[i][j].holder();
          i++;
        } else {
          if (board[i][j].emptiness()) {
            cout << B_GREEN << "   ";
          } else {
            cout << B_GREEN << "   ";
          }
          //cout << B_GREEN << board[i][j].holder();
          i++;
        }
      }
    }
    cout << RESET << endl;
    i = 0;
    j++;
  }

  cout << RESET << endl;
}

/* MAKE_MOVE */
void Othello::make_move(const std::string &move) // flips piece A3
{
  int row, col;
  row = int(move[1] - '1');
  col = int(toupper(move[0]) - 'A');
  int i = col;
  int j = row;
  bool up, up_right, right, down_right, down, down_left, left, up_left;

  if (move != "xx") {

    up = check_up(move);
    up_right = check_up_right(move);
    right = check_right(move);
    down_right = check_down_right(move);
    down = check_down(move);
    down_left = check_down_left(move);
    left = check_left(move);
    up_left = check_up_left(move);

    if (current_color() == "white") {
      board[col][row].set_piece_white();
    } else if (current_color() == "black") {
      board[col][row].set_piece_black();
    }
  }

  // If a skip was inputted
  else {
    up = false;
    up_right = false;
    right = false;
    down_right = false;
    down = false;
    left = false;
    up_left = false;
  }

  // FLIPPING ALL OPPOSITE PIECES IN UP DIRECTION
  if (up == true) {
    // cout<<"Up flip is activated\n";
    int row, col;
    row = int(move[1] - '1');
    col = int(toupper(move[0]) - 'A');
    int i = col;
    int j = row;

    while (((board[i][j - 1].has_piece_color()) != (current_color())) &&
           (j >= 0)) {
      board[i][j - 1].flip();
      j = j - 1;
    }
  }

  // FLIPPING ALL OPPOSITE PIECES IN UP_RIGHT DIRECTION
  if (up_right == true) {
    // cout<<"Up right flip is activated\n";
    int row, col;
    row = int(move[1] - '1');
    col = int(toupper(move[0]) - 'A');
    int i = col;
    int j = row;

    while (((board[i + 1][j - 1].has_piece_color()) != (current_color())) &&
           (i < 8 && j >= 0)) {
      board[i + 1][j - 1].flip();
      j = j - 1;
      i = i + 1;
    }
  }

  // FLIPPING ALL OPPOSITE PIECES IN RIGHT DIRECTION
  if (right == true) {
    // cout<<"Right flip is activated\n";
    int row, col;
    row = int(move[1] - '1');
    col = int(toupper(move[0]) - 'A');
    int i = col;
    int j = row;

    while (((board[i + 1][j].has_piece_color()) != (current_color())) &&
           (i < 8)) {
      board[i + 1][j].flip();
      i = i + 1;
    }
  }

  // FLIPPING ALL OPPOSITE PIECES IN DOWN_RIGHT DIRECTION
  if (down_right == true) {
    // cout<<"Down right flip is activated \n";
    int row, col;
    row = int(move[1] - '1');
    col = int(toupper(move[0]) - 'A');
    int i = col;
    int j = row;

    while (((board[i + 1][j + 1].has_piece_color()) != (current_color())) &&
           (j < 8 && i < 8)) {
      board[i + 1][j + 1].flip();
      j = j + 1;
      i = i + 1;
    }
  }

  // FLIPPING ALL OPPOSITE PIECES IN DOWN DIRECTION
  if (down == true) {
    // cout<<"Down flip is activated \n";
    int row, col;
    row = int(move[1] - '1');
    col = int(toupper(move[0]) - 'A');
    int i = col;
    int j = row;

    while (((board[i][j + 1].has_piece_color()) != (current_color())) &&
           (j < 8)) {
      board[i][j + 1].flip();
      j = j + 1;
    }
  }

  // FLIPPING ALL OPPOSITE PIECES IN DOWN_LEFT DIRECTION
  if (down_left == true) {
    // cout<<"Down Left flip is activated \n";
    int row, col;
    row = int(move[1] - '1');
    col = int(toupper(move[0]) - 'A');
    int i = col;
    int j = row;

    while (((board[i - 1][j + 1].has_piece_color()) != (current_color())) &&
           ((i >= 0) && (j < 8))) {
      board[i - 1][j + 1].flip();
      i = i - 1;
      j = j + 1;
    }
  }

  // FLIPPING ALL OPPOSITE PIECES IN LEFT DIRECTION
  if (left == true) {
    // cout<<"Left flip is activated\n";
    int row, col;
    row = int(move[1] - '1');
    col = int(toupper(move[0]) - 'A');
    int i = col;
    int j = row;

    while (((board[i - 1][j].has_piece_color()) != (current_color())) &&
           (i >= 0)) {
      board[i - 1][j].flip();
      i = i - 1;
    }
  }

  // FLIPPING ALL OPPOSITE PIECES IN UP_LEFT DIRECTION
  if (up_left == true) {
    // cout<<"Up Left flip is activated\n";
    int row, col;
    row = int(move[1] - '1');
    col = int(toupper(move[0]) - 'A');
    int i = col;
    int j = row;

    while (((board[i - 1][j - 1].has_piece_color()) != (current_color())) &&
           ((i >= 0) && (j >= 0))) {
      board[i - 1][j - 1].flip();
      j = j - 1;
      i = i - 1;
    }
  }

  game::make_move(move);
}

/* IS_LEGAL */
bool Othello::is_legal(const std::string &move) const {
  if (move == "xx") {
    return true;
  }
  if (checker(move) == true) {
    return true;
  } else {
    return false;
  }
}

/* RESTART */
void Othello::restart() {
  for (int j = 0; j < 8; j++) // Double for loop empties the board
  {
    for (int i = 0; i < 8; i++) {
      board[i][j].set_as_empty();
    }
  }
  /*places the initial 4 pieces*/
  board[3][3].set_piece_white();
  board[4][4].set_piece_white();
  board[3][4].set_piece_black();
  board[4][3].set_piece_black();
}

/*BELOW ARE THE HELPER FUNCTIONS THAT HELP WITH ISLEGAL AND MAKEMOVE */

// RETURNS COLOR OF ENTITY MAKING CURRENT MOVE

string Othello::current_color() const {
  int x = moves_completed();
  if ((x % 2) == 0) {
    return "black";
  } else {
    return "white";
  }
}

// CHECKER - CHECKS IF MOVE IS LEGAL
bool Othello::checker(const string &move) const {
  bool up, up_right, right, down_right, down, down_left, left,
      up_left; // variables that determine viability of each move
  int row, col;
  row = int(move[1] - '1');
  col = int(toupper(move[0]) - 'A');
  if (board[col][row].has_piece_color() !=
      "empty") // If there is already a piece in that  spot you cant go there
  {
    return false;
  }

  // Checking all 8 directions from given location for legality
  up = check_up(move);
  up_right = check_up_right(move);
  right = check_right(move);
  down_right = check_down_right(move);
  down = check_down(move);
  down_left = check_down_left(move);
  left = check_left(move);
  up_left = check_up_left(move);

  if ((up || up_right || right || down_right || down || down_left || left ||
       up_left) == true) {
    return true;
  } else {
    return false;
  }
}

// CHECK UP
bool Othello::check_up(const string &move) const {
  int row, col;
  row = int(move[1] - '1');
  col = int(toupper(move[0]) - 'A');
  int i = col;
  int j = row;

  while ((j - 2) >= 0) {
    if (((board[i][j - 1].has_piece_color()) == "empty") ||
        (board[i][j - 1].has_piece_color() == current_color())) {
      return false;
    }
    if (((board[i][j - 1].has_piece_color()) != (current_color())) &&
        ((board[i][j - 2].has_piece_color()) == (current_color()))) {
      return true;
    }
    j = j - 1;
  }
  return false;
}

// CHECK UP RIGHT
bool Othello::check_up_right(const string &move) const {
  int row, col;
  row = int(move[1] - '1');
  col = int(toupper(move[0]) - 'A');
  int i = col;
  int j = row;
  while (((i + 2) < 8) && ((j - 2) >= 0)) {
    if (((board[i + 1][j - 1].has_piece_color()) == "empty") ||
        (board[i + 1][j - 1].has_piece_color() == current_color())) {
      return false;
    }
    if (((board[i + 1][j - 1].has_piece_color()) != (current_color())) &&
        ((board[i + 2][j - 2].has_piece_color()) == (current_color()))) {
      return true;
    }
    j = j - 1;
    i = i + 1;
  }
  return false;
}

// CHECK RIGHT
bool Othello::check_right(const string &move) const {
  int row, col;
  row = int(move[1] - '1');
  col = int(toupper(move[0]) - 'A');
  int i = col;
  int j = row;

  while ((i + 2) < 8) {
    if (((board[i + 1][j].has_piece_color()) == "empty") ||
        (board[i + 1][j].has_piece_color() == current_color())) {
      return false;
    }
    if (((board[i + 1][j].has_piece_color()) != (current_color())) &&
        ((board[i + 2][j].has_piece_color()) == (current_color()))) {
      return true;
    }
    i = i + 1;
  }
  return false;
}

// CHECK DOWN RIGHT
bool Othello::check_down_right(const string &move) const {
  int row, col;
  row = int(move[1] - '1');
  col = int(toupper(move[0]) - 'A');
  int i = col;
  int j = row;

  while (((i + 2) < 8) && ((j + 2) < 8)) {
    if (((board[i + 1][j + 1].has_piece_color()) == "empty") ||
        ((board[i + 1][j + 1].has_piece_color()) == current_color())) {
      return false;
    }
    if (((board[i + 1][j + 1].has_piece_color()) != (current_color())) &&
        ((board[i + 2][j + 2].has_piece_color()) == (current_color()))) {
      return true;
    }
    j = j + 1;
    i = i + 1;
  }
  return false;
}

// CHECK DOWN
bool Othello::check_down(const string &move) const {
  int row, col;
  row = int(move[1] - '1');
  col = int(toupper(move[0]) - 'A');
  int i = col;
  int j = row;
  while ((j + 2) < 8) {
    if (((board[i][j + 1].has_piece_color()) == "empty") ||
        ((board[i][j + 1].has_piece_color()) == current_color())) {
      return false;
    }
    if (((board[i][j + 1].has_piece_color()) != (current_color())) &&
        ((board[i][j + 2].has_piece_color()) == (current_color()))) {
      return true;
    }
    j = j + 1;
  }
  return false;
}

// CHECK DOWN LEFT
bool Othello::check_down_left(const string &move) const {
  int row, col;
  row = int(move[1] - '1');
  col = int(toupper(move[0]) - 'A');
  int i = col;
  int j = row;
  while (((i - 2) >= 0) && ((j + 2) < 8)) {
    if (((board[i - 1][j + 1].has_piece_color()) == "empty") ||
        ((board[i - 1][j + 1].has_piece_color()) == (current_color()))) {
      return false;
    }
    if (((board[i - 1][j + 1].has_piece_color()) != (current_color())) &&
        ((board[i - 2][j + 2].has_piece_color()) == (current_color()))) {
      return true;
    }
    j = j + 1;
    i = i - 1;
  }
  return false;
}

// CHECK LEFT
bool Othello::check_left(const string &move) const {
  int row, col;
  row = int(move[1] - '1');
  col = int(toupper(move[0]) - 'A');
  int i = col;
  int j = row;
  while ((i - 2) >= 0) {
    if (((board[i - 1][j].has_piece_color()) == "empty") ||
        (board[i - 1][j].has_piece_color() == current_color())) {
      return false;
    }
    if (((board[i - 1][j].has_piece_color()) != (current_color())) &&
        ((board[i - 2][j].has_piece_color()) == (current_color()))) {
      return true;
    }
    i = i - 1;
  }
  return false;
}

// CHECK UP LEFT
bool Othello::check_up_left(const string &move) const {
  int row, col;
  row = int(move[1] - '1');
  col = int(toupper(move[0]) - 'A');
  int i = col;
  int j = row;
  while (((i - 2) >= 0) && ((j - 2) >= 0)) {
    if (((board[i - 1][j - 1].has_piece_color()) == "empty") ||
        (board[i - 1][j - 1].has_piece_color() == current_color())) {
      return false;
    }
    if (((board[i - 1][j - 1].has_piece_color()) != (current_color())) &&
        ((board[i - 2][j - 2].has_piece_color()) == (current_color()))) {
      return true;
    }
    j = j - 1;
    i = i - 1;
  }
  return false;
}

/* VICTORY */
void Othello::victory() const {

  int empty_counter = 0;
  int white_counter = 0;
  int black_counter = 0;
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if (board[i][j].has_piece_color() == "empty") {
        empty_counter++;
      }
      if (board[i][j].has_piece_color() == "black") {
        black_counter++;
      } else if (board[i][j].has_piece_color() == "white") {
        white_counter++;
      }
    }
  }
  cout << "Game Over\n";
  if (black_counter > white_counter) {
    cout << "Black wins!\n";
    cout << " Black:" << black_counter << " White:" << white_counter << endl;
  } else if (white_counter > black_counter) {
    cout << "White wins!\n";
    cout << " White:" << white_counter << " Black:" << black_counter << endl;
  } else {
    cout << "Tie game!\n";
  }
}

string Othello::get_board_as_string() const {
  string result = "";
  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
      if (board[col][row].emptiness()) {
        result += "-";
      } else if (board[col][row].has_piece_color() == "black") {
        result += "x";
      } else if (board[col][row].has_piece_color() == "white") {
        result += "o";
      }
    }
    result += "\n";
  }
  return result;
}