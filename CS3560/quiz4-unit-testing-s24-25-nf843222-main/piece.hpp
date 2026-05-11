/**
 * @file piece.hpp
 * @author Taylor Bruening
 * @brief Header file for piece class
 */
#include "colors.hpp"
#include <cstdlib>
#include <iostream>
#include <string>

#ifndef OTHELLO_PIECE
#define OTHELLO_PIECE

/**
 * @brief Abstraction of a piece on the board.
 * 
 * Although, it is more like a tile.
 * 
*/
class piece {
public:
  /** 
   * @brief Defult constructor.
   * 
   * Defult contructor that set both empty and color to true (black piece)
   */
  piece() {
    empty = true;
    color = true;
  }

  /** Constructor that take all attributes.
   */
  piece(bool empty, bool color) : empty(empty), color(color) {}

  // ACCESSORS
  const std::string holder() const;

  const bool emptiness() const;

  /**
   * Return a string of black, white or empty depending on the state of the piece.
  */
  const std::string has_piece_color() const;

  // MUTATORS
  void set_piece_black() {
    color = true;
    empty = false;
  }

  void set_piece_white() {
    color = false;
    empty = false;
  }

  /**
   * Set the piece as empty, but does not clear the color.
  */
  void set_as_empty() { empty = true; }

  /**
   * If the piece has color, flip the color of the piece
  */
  void flip();

private:
  bool empty;
  bool color; /// true refer to a black piece, otherwise a white piece.
};

#endif
