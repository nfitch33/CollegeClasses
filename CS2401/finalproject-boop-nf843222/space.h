

#ifndef SPACE_H
#define SPACE_H

#include <string>
#include <iostream>
using namespace std;


class space{
    public:
        space();
        bool is_empty() const {return empty;} // Checks if square is empty
        bool get_color() const {return color;} // Back up for Ccolor, for some reason this one is used for multiple if(parameters)
        char get_piece() const {return piece;} // Gets piece back, to check if guitar or music note
        void set_Rpiece(char option) {piece = option;} // Replaces the piece during booping pieces phase
        void set_Rcolor() {color = true;}   // Makes squares belong to player 1
        void set_Rempty() {empty = true;}   // Clearing squares sets back to empty
        void set_Npiece(string option) {piece = option.at(0);} // Gets new piece from what was entered as users move
        void set_Ncolor() {color = false;}  // Makes squares belong to player 2
        void set_Nempty() {empty = false;} // If put on square, sets as not empty
        bool get_Ccolor() {return color;}   // Grabs color for commparisoon operators, For direct true or false parameters
        // void change(string piece, string color);
        // void getter();
    private:
        bool color;
        char piece;
        bool empty;
};
#endif


/* NOTE
 |\
 |
@|
*/

/*  GUIITAR

(o\_)=="#

*/

// PLAYER 2 || BLUE == FALSE
// PLAYER 1 || RED == TRUE

// HUMAN = RED