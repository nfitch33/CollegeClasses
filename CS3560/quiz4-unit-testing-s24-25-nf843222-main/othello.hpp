/**
 * @file othello.hpp
 * @author Taylor Bruening
 * @brief Header file for Othello class
 */
#include <cstdlib>
#include <exception>
#include <iostream>
#include <queue>
#include <string>

#include "colors.hpp"
#include "game.hpp"
#include "piece.hpp"
#include "utils.hpp"

#ifndef OTHELLO_GAME
#  define OTHELLO_GAME

class Othello : public main_savitch_14::game {
public:
  /**
   * @brief Default constructor.
   */
  Othello() {}

  /**
   * @brief Contructor accepting a string representing a board.
   *
   * A dash (-) is used to indicate the empty space. The x is used to indicate
   * a black piece, the o is used to indicate a white piece.
   *
   * Correctness of the starting board will not be validate.
   */
  Othello(std::string board_text) {
    auto lines = split_by(board_text, "\n");

    int i = 0;
    for (auto line : lines) {
      int j = 0;
      for (auto t : line) {
        // x == black piece
        if (t == 'x') {
          board[j][i].set_piece_black();
        } else if (t == 'o') {
          // o == white piece
          board[j][i].set_piece_white();
        } else if (t == '-') {
          board[j][i].set_as_empty();
        }
        j += 1;
      }
      i += 1;
    }
  }

  /**
   * @brief Contructor accepting a vector of board lines.
   *
   * A dash (-) is used to indicate the empty space. The x is used to indicate
   * a black piece, the o is used to indicate a white piece.
   *
   * Correctness of the starting board will not be validate.
   */
  Othello(std::vector<std::string> board_lines) {
    if (board_lines.size() != 8) {
      throw std::runtime_error("board size is greter than 8x8");
    }

    int i = 0;
    for (auto line : board_lines) {
      int j = 0;
      for (auto t : line) {
        // x == black piece
        if (t == 'x') {
          board[j][i].set_piece_black();
        } else if (t == 'o') {
          // o == white piece
          board[j][i].set_piece_white();
        } else if (t == '-') {
          board[j][i].set_as_empty();
        }
        j += 1;
      }
      i += 1;
    }
  }

  /**
   * @brief Contructor accepting raw board data
   *
   * This is not tested.
   *
   * Correctness of the starting board will not be validate.
   */
  /*Othello(const piece b[8][8]) : game() {
    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
        board[i][j] = b[i][j];
      }
    }
  }*/

  // PHASE1-2 FUNCTIONS
  void display_status() const;

  void make_move(const std::string &move);

  bool is_legal(const std::string &move) const;

  bool is_game_over() const;

  /**
   * Restart the game.
   *
   * This can be used to reset the board. Since the constructor
   * does not initialize the board, this function has to be used
   * to create the starting board.
   */
  void restart();

  void victory() const;

  // PHASE 3 FUNCTIONS
  /**
   * Evaluate the board status.
   *
   * Note that the return value change depending on who the current player is. For example,
   * the following board
   *
   * <pre>
   * --------
   * --------
   * ---x----
   * ---xx---
   * ---xo---
   * --------
   * --------
   * --------
   * </pre>
   *
   * will return <code>1</code> if the current player is the black piece and <code>-1</code> if the
   * current player is the white piece. The first turn is the human player who controls the
   * black pieces.
   *
   * Note: x is the black piece, o is the white piece and the dash (-) is the empty tile.
   *
   * @return 1 if the board is in favor of the current player.
   * @return -1 if the board is in favor of the other player.
   * @return 0 if the  board equally favor both side.
   */
  int evaluate() const;

  void compute_moves(std::queue<std::string> &moves) const;

  game *clone() const;

  // FUNCTIONS USED TO TRAVERSE BOARD
  std::string current_color() const;
  bool checker(const string &move) const;
  bool check_up(const string &move) const;
  bool check_up_right(const string &move) const;
  bool check_right(const string &move) const;
  bool check_down_right(const string &move) const;
  bool check_down(const string &move) const;
  bool check_down_left(const string &move) const;
  bool check_left(const string &move) const;
  bool check_up_left(const string &move) const;

  // Utility functions
  /**
   * Return a string that representing the board.
   *
   * @return a string that representing the board.
   */
  std::string get_board_as_string() const;

private:
  piece board[8][8];
};

#endif
