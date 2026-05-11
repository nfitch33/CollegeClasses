#pragma once

#include <iostream>
#include "game.hpp"
#include "piece.hpp"
#include "colors.hpp"
using namespace std;

namespace main_savitch_14
{

class Othello: public game {
public:

	Othello() {}

	void display_status()const;
	int evaluate()const;
	bool is_game_over()const;

	/**
	 * @brief checks if chosen move is allowed and returns boolean , true if allowed, false if not allowed
	 * @param move the current move being checked
	 * @return false if move is not allowed
	 * @return true if move is allowed
	 */
	bool is_legal(const string& move)const;
	
	void make_move(const string& move);
	void restart();
	void make_skips();
	void countingPieces();
	void whosTurn();
	game* clone()const{return new Othello(*this);}
	void compute_moves(std::queue<std::string>& moves)const;
	who winning()const;

protected:
	int black;
	int white;
	int skips;
	int openSpots;
	int b;
	int w;

private:
	piece gameBoard[8][8];
};
}
