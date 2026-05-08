

#ifndef BOOP_H
#define BOOP_H

#include "space.h"
#include "game.h"
#include <queue>

using namespace main_savitch_14;
static const int i = 6; // Rows of board
static const int j = 6; // Columns of board
class Boop:public game {
    public:
        Boop();
        void create_board(); // Extra function to test compilation
        void restart(); // Sets all default values for game
        void display_status() const; // Prints the board and pieces left in terminal
        void player_move(); // gets players move
        void make_move(const std::string &move); // Puts move onto the board
        bool is_legal(const std::string& option) const; // Checks to make sure player move is legal
        game* clone() const {return nullptr;}
        void compute_moves(std::queue<std::string>& moves) const;
        int evaluate() const;
        bool is_game_over() const;
        bool checkThree(bool color);
        void boopAdj(const std::string& move);
        void computer_Moves(std::queue<std::string>& moves);
        bool checkCthree() const;
    private:
        int player2_small; // Smalls are guitars
        int player2_large; // Bigs are music notes
        int player1_small;
        int player1_large; 
        int newMOVE;
        std::queue<std::string> moves;
        space array[i][j]; // Board
};
#endif
