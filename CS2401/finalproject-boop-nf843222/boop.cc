

#include "boop.h"
#include "colors.h"
#include "space.h"
#include "game.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <queue>
using namespace std;


Boop::Boop(){; // Calls restart function
    restart();
}

void Boop::create_board(){ // Extra function
    cout << "HELLO" << endl;
}
void Boop::restart(){ // Sets all default values
    char option = '0';
    for(int i = 0; i < 7; i++){
        for(int j = 0; j < 7; j++){
            array[i][j].set_Rempty();
            array[i][j].set_Rcolor();
            array[i][j].set_Rpiece(option);
        }
    }
    player2_small = 8;
    player2_large = 0; // Large pieces will be set to 0 later
    player1_small = 8;
    player1_large = 0;
    newMOVE = 0;
    while(!(moves.empty())){
        moves.pop();
    }
    game::restart();
}

void Boop::display_status() const{ // Draws the board
    int size = 7;
    char tmp = 'A';
    cout << setw(8) << setfill(' ') << tmp;
    tmp++;
    for(int x = 0; x < 5; x++){
        cout << setw(11) << tmp;
        tmp++;
    }
    cout << endl;
    for(int i = 1; i < size; i++){ // Rows
        cout << setw(70) << setfill('-') << "-" << endl;
        for(int k = 1; k < 4; k++){
            if(k == 1){ // Starts with first line of each box
                for(int j = 1; j < size; j++){ // Columns
                    if(array[i][j].get_piece() == 'n' || array[i][j].get_piece() == 'N'){
                        if(array[i][j].get_color() == true){
                            cout << WHITE << " | " << RED << "    |\\  " << WHITE;
                        }
                        else{
                            cout << WHITE << " | " << BLUE << "    |\\  " << WHITE;
                        }
                    }
                    else if(array[i][j].get_piece() == 'g' || array[i][j].get_piece() == 'G'){ 
                        if(array[i][j].get_color() == true){
                            cout << WHITE << " |         " << RED << "" << WHITE;
                        }
                        else{
                            cout << WHITE << " |         " << BLUE << "" << WHITE;
                        }

                    }
                    else{
                        cout << " |         ";
                    }
                }
                cout << "  |" << endl;
            }
            else if(k == 2){ // Second line of each box
                cout << i;
                for(int j = 1; j < size; j++){ // Column
                    if(array[i][j].get_piece() == 'n' || array[i][j].get_piece() == 'N'){
                        if(array[i][j].get_color() == true){
                            cout << WHITE << "| " << RED << "    |    " << WHITE;
                        }
                        else{
                            cout << WHITE << "| " << BLUE << "    |    " << WHITE;
                        }
                    }
                    else if(array[i][j].get_piece() == 'g' || array[i][j].get_piece() == 'G'){
                        if(array[i][j].get_color() == true){
                            cout << WHITE << "|" << RED << " (o\\_)==\"#" << WHITE;
                        }
                        else{
                            cout << WHITE << "|" << BLUE << " (o\\_)==\"#" << WHITE;
                        }

                    }
                    else{
                        cout << "|          ";
                    }
                }
                cout << " |" << endl;
            }
            else{ // 3rd line of boxes
                for(int j = 1; j < size; j++){ // Columns
                    if(array[i][j].get_piece() == 'n' || array[i][j].get_piece() == 'N'){
                        if(array[i][j].get_color() == true){
                            cout << WHITE << " | " << RED << "   @|   " << WHITE;
                        }
                        else{
                            cout << WHITE << " | " << BLUE << "   @|   " << WHITE;
                        }
                    }
                    else if(array[i][j].get_piece() == 'g' || array[i][j].get_piece() == 'G'){
                        if(array[i][j].get_color() == true){
                            cout << WHITE << " |         " << RED << "" << WHITE;
                        }
                        else{
                            cout << WHITE << " |         " << BLUE << "" << WHITE;
                        }

                    }
                    else{
                       cout << " |         ";
                    }
            }
                cout << "  |" << endl;
        }
    }
    }
    cout << setw(70) << setfill('-') << '-' << endl; // Bottom line
    cout << endl;
    cout << RED << "Player 1 - (G)Guitars left: " << player1_small;
    cout << "           ";
    cout << BLUE << "Player 2 - (G)Guitars left: " << player2_small << endl;
    cout << RED << "Player 1 - (N)Music Notes Left: " << player1_large;
    cout << "       ";
    cout << BLUE << "Player 2 - (N)Music Notes Left: " << player2_large << WHITE << endl;
}

bool Boop::is_legal(const string& option) const{ // Checks to make sure if player moves are legal
    int row = option.at(1) - '1' + 1;
    int column = toupper(option.at(2)) - 'A' + 1;
    if(option.size() != 3){ // If move is larger than 3 sections
        cout << "Invalid choice, Try again" << endl;
        return false;
    }
    else if(option.at(0) != 'g' && option.at(0) != 'G' && option.at(0) != 'n' && option.at(0) != 'N'){ // If piece is not a guitar or music note
        cout << "Invalid piece, try again" << endl;
        return false;
    }
    else if((option.at(1) < '1' || option.at(1) > '6')){ // Checks to make sure if row is valid
        cout << "Invalid Row, try again" << endl;
        return false;
    }
    else if((option.at(2) > 'F' && option.at(2) < 'A') || (option.at(2) > 'f' && option.at(2) < 'a')){ // Checks to make sure column is valid
        cout << "Invalid Column, try again" << endl;
        return false;
    }
    else if(((array[row][column]).is_empty()) == false){ // Checks if space is empty
        cout << "Space is not empty, try again" << endl;
        return false;
    }
    else{
        if(option.at(0) == 'g' || option.at(0) == 'G'){ // Checking to make sure players have pieces
            if(game::next_mover() == HUMAN){
                if(player1_small == 0){
                    cout << "No more of selected piece, try again" << endl;
                    return false;
                }
            }
            else{
                if(player2_small == 0){
                    cout << "No more of selected piece, try again" << endl;
                    return false;
                }
            }
        }
        else{
            if(game::next_mover() == HUMAN){        // Checking if players have pieces
                if(player1_large == 0){
                    cout << "No more of selected piece, try again" << endl;
                    return false;
                }
            }           
            else{
                if(player2_large == 0){
                    cout << "No more of selected piece, try again" << endl;
                    return false;
                }
            }
        }
        return true;
    }
}

void Boop::make_move(const string &move){ // Does all the hard work off the code placing pieces
    if(!(next_mover() == HUMAN)){
        compute_moves(moves);
        computer_Moves(moves);
    }
    else{
    int row, column;
    bool color;
    int whileCounter;
    char allSpots;
    char tempCR = 'q';
    /*MAKE SURE TO GO THROUGH ALL MOVE LINKS BELOW*/
    if(move == "000" && next_mover() == HUMAN){ // Need to take one off
            cout << "NO PIECES" << endl;
            newMOVE = 2;
            color = true;
    }
    else if(move == "111" && !(next_mover() == HUMAN)){
            cout << "NO PIECES" << endl;
            newMOVE = 2;
            color = false;
    }
    /*PLACING PIECES*/ /*NEED TO WRITE TO BOOP ALL PIECES*/ /*NEED TO WRITE CHECK FOR 3 IN A ROW*/ /*CHECK IF ALL 8 PIECES ARE ON BOARD*/
    if(newMOVE != 2){
    if(is_legal(move) == true){
        boopAdj(move);
        row = move.at(1);
        row = row - '1' + 1;        // Sets row to correct integer value

        column = toupper(move.at(2));
        column = column - 'A' + 1;  // Sets column to correct integer value

        if(game::next_mover() == HUMAN){
            array[row][column].set_Rcolor();    // If move is legal, sets color of place to one player
        }
        else{
            array[row][column].set_Ncolor();
        }
        array[row][column].set_Nempty();    // Sets place as not empty
        cout << row << column << endl;
        cout << array[row][column].is_empty() << endl;
        array[row][column].set_Npiece(move);
        if(move.at(0) == 'g' || move.at(0) == 'G'){
            if(array[row][column].get_Ccolor() == true){    // Removes one piece from the storage
                player1_small--;
            }
            else{
                player2_small--;
            }
        }
        else{
            if(array[row][column].get_Ccolor() == true){    // Gets rid of a large piece if one was placed
                player1_large--;
            }
            else{
                player2_large--;
            }
        }
        }
        else{
            player_move();
        }   
        if(game::next_mover() == HUMAN){
            color = true;
        }
        else{
            color = false;
        }
        if(checkThree(color) == true && is_game_over() == false){ // IF 3 of a kind are on board
            newMOVE = 1;
        }
        if(newMOVE == 1){
            
            display_status();
            char aligned;
            int whileCounter = 0;
            while(whileCounter == 0){
                cout << "THREE IN A ROW" << endl;   // Prints out to let user know there is three in a row
                cout << "Which way are the pieces aligned? \\|/- ";
                cin >> aligned;
                while(aligned != '\\' && aligned != '|' && aligned != '/' && aligned != '-'){
                    cout << "Which way are the pieces aligned? \\|/- ";
                    cin >> aligned;
                }
                if(aligned == '\\'){ // TOP LEFT TO BOTTOM RIGHT
                    cout << "What Row is the middle piece? (1-6) ";
                    cin >> allSpots;
                    row = allSpots - '1' + 1;
                    cout << row << endl;
                    cout << "What Column is the middle piece? (A-F) ";
                    cin >> allSpots;
                    column = toupper(allSpots) - 'A' + 1;
                    cout << column << endl;
                    if(row - 1 <= 0 || row + 1 >= 6 || column - 1 <= 0 || column + 1 > 6){
                        cout << "Not possible parameters try again" << endl;
                    }
                    else{
                        if(array[row][column].get_color() == color){
                            if(array[row-1][column-1].get_color() == color){ // top left
                                if(array[row+1][column+1].get_color() == color){ // bottom right
                                     if(color == false){
                                        array[row-1][column-1].set_Rpiece(tempCR);
                                        array[row-1][column-1].set_Rempty();
                                        player2_large++;
                                        array[row+1][column+1].set_Rpiece(tempCR);
                                        array[row+1][column+1].set_Rempty();
                                        player2_large++;
                                        array[row][column].set_Rpiece(tempCR);
                                        array[row][column].set_Rempty();
                                        player2_large++;
                                    }   // ADDS 3 Large pieces for getting rid of three pieces
                                    else{
                                        array[row-1][column-1].set_Rpiece(tempCR);
                                        array[row-1][column-1].set_Rempty();
                                        player1_large++;
                                        array[row+1][column+1].set_Rpiece(tempCR);
                                        array[row+1][column+1].set_Rempty();
                                        player1_large++;
                                        array[row][column].set_Rpiece(tempCR);
                                        array[row][column].set_Rempty();
                                        player1_large++;
                                    }
                                }
                                else{
                                    cout << "Bottom right is not your piece or out of bounds" << endl;
                                }
                            }
                            else{
                                cout << "Top left is not your piece or out of bounds" << endl;
                            }
                        }
                        else{
                            cout << "Selected Place is not a square you control" << endl;
                        }
                    
                    }
                    whileCounter++;
                }
                else if(aligned == '|'){ // TOP TO BOTTOM
                    cout << "What Row is the middle piece? (1-6) ";
                    cin >> allSpots;
                    row = allSpots - '1' + 1;
                    cout << row << endl;
                    cout << "What Column is the middle piece? (A-F) ";
                    cin >> allSpots;
                    column = toupper(allSpots) - 'A' + 1;
                    cout << column << endl;
                    if(row - 1 <= 0 || row + 1 > 6){
                        cout << "Not Possible Parameters, Try again" << endl;
                    }
                    else{
                        if(array[row][column].get_color() == color){
                            if(array[row-1][column].get_color() == color){ // top middle
                                if(array[row+1][column].get_color() == color){ // bottom middle
                                    if(color == false){
                                        array[row-1][column].set_Rpiece(tempCR);
                                        array[row-1][column].set_Rempty();
                                        player2_large++;
                                        array[row][column].set_Rpiece(tempCR);
                                        array[row][column].set_Rempty();
                                        player2_large++;
                                        array[row+1][column].set_Rpiece(tempCR);
                                        array[row+1][column].set_Rempty();
                                        player2_large++;
                                    }
                                    else{
                                        array[row-1][column].set_Rpiece(tempCR);
                                        array[row-1][column].set_Rempty();
                                        player1_large++;
                                        array[row][column].set_Rpiece(tempCR);
                                        array[row][column].set_Rempty();
                                        player1_large++;
                                        array[row+1][column].set_Rpiece(tempCR);
                                        array[row+1][column].set_Rempty();
                                        player1_large++;
                                    }
                                }
                                else{
                                    cout << "Top Middle is not your piece or out of bounds" << endl;
                                }
                            }
                            else{
                                cout << "Bottom Middle is not your piece or out of bounds" << endl;
                            }
                        }
                        else{
                            cout << "Selected Piece is not a square you conrol" << endl;
                        }
                    }
                    whileCounter++;
                }
                else if(aligned == '/'){ // TOP RIGHT TO BOTTOM LEFT
                    cout << "What Row is the middle piece? (1-6) ";
                    cin >> allSpots;
                    row = allSpots - '1' + 1;
                    cout << row << endl;
                    cout << "What Column is the middle piece? (A-F) ";
                    cin >> allSpots;
                    column = toupper(allSpots) - 'A' + 1;
                    cout << column << endl;
                    if(row - 1 <= 0 || row + 1 > 6 || column - 1 <= 0 || column + 1 > 6){
                        cout << "Not possible parameters try again" << endl;
                    }
                    else{
                        if(array[row][column].get_color() == color){
                            if(array[row-1][column+1].get_color() == color){ // top right
                                if(array[row+1][column-1].get_color() == color){ // bottom left
                                    if(color == false){
                                        array[row+1][column-1].set_Rpiece(tempCR);
                                        array[row+1][column-1].set_Rempty();
                                        player2_large++;
                                        array[row-1][column+1].set_Rpiece(tempCR);
                                        array[row-1][column+1].set_Rempty();
                                        player2_large++;
                                        array[row][column].set_Rpiece(tempCR);
                                        array[row][column].set_Rempty();
                                        player2_large++;
                                    }
                                    else{
                                        array[row+1][column-1].set_Rpiece(tempCR);
                                        array[row+1][column-1].set_Rempty();
                                        player1_large++;
                                        array[row-1][column+1].set_Rpiece(tempCR);
                                        array[row-1][column+1].set_Rempty();
                                        player1_large++;
                                        array[row][column].set_Rpiece(tempCR);
                                        array[row][column].set_Rempty();
                                        player1_large++;
                                    }
                                }
                                else{
                                    cout << "Top right is not your piece or out of bounds" << endl;
                                }
                            }
                            else{
                                cout << "Bottom Left is not your piece or out of bounds" << endl;
                            }
                        }
                        else{
                            cout << "Selected Piece is not a square you conrol" << endl;
                        }
                    }
                    whileCounter++;
                }
                else if(aligned == '-'){ // LEFT TO RIGHT
                    cout << "What Row is the middle piece? (1-6) ";
                    cin >> allSpots;
                    row = allSpots - '1' + 1;
                    cout << row << endl;
                    cout << "What Column is the middle piece? (A-F) ";
                    cin >> allSpots;
                    column = toupper(allSpots) - 'A' + 1;
                    cout << column << endl;
                    if(column - 1 <= 0 || column + 1 > 6){
                        cout << "Not Possible Parameters, Try again" << endl;
                    }
                    else{
                        if(array[row][column].get_color() == color){
                            if(array[row][column-1].get_color() == color){ // Left
                                if(array[row][column+1].get_color() == color){ // Right
                                    if(color == false){
                                        array[row][column-1].set_Rpiece(tempCR);
                                        array[row][column-1].set_Rempty();
                                        player2_large++;
                                        array[row][column+1].set_Rpiece(tempCR);
                                        array[row][column+1].set_Rempty();
                                        player2_large++;
                                        array[row][column].set_Rpiece(tempCR);
                                        array[row][column].set_Rempty();
                                        player2_large++;
                                    }
                                    else{
                                        array[row][column-1].set_Rpiece(tempCR);
                                        array[row][column-1].set_Rempty();
                                        player1_large++;
                                        array[row][column+1].set_Rpiece(tempCR);
                                        array[row][column+1].set_Rempty();
                                        player1_large++;
                                        array[row][column].set_Rpiece(tempCR);
                                        array[row][column].set_Rempty();
                                        player1_large++;
                                    }
                                }
                                else{
                                    cout << "Left is not your piece or out of bounds" << endl;
                                }
                            }
                            else{
                                cout << "Right is not your piece or out of bounds" << endl;
                            }
                        }
                        else{
                            cout << "Selected Piece is not a square you conrol" << endl;
                        }
                    }
                    whileCounter++;
                }
            }
        }
    }
        if(newMOVE == 2){ // IF there was not three of a kind and player has no available pieces

            while(whileCounter == 0){
                cout << "All pieces are on board, which would you like to take off?" << endl;
                cout << "What is the row of your piece (1-6)" << endl;
                cin >> allSpots;
                row = allSpots - '1' + 1;
                cout << row << endl;
                cout << "What is the column of your piece (A-F)" << endl;
                cin >> allSpots;
                column = allSpots - 'A' + 1;
                cout << column;
                if(next_mover() == HUMAN){
                    color = true;
                }
                else{
                    color = false;
                }
                if(row <= 0 || row > 6 || column <= 0 || column > 6){
                    cout << "Sorry but that is not a square in your control" << endl;
                }
                else{
                    if(array[row][column].get_color() == color){
                        whileCounter++;
                        array[row][column].set_Rempty();
                        array[row][column].set_Rpiece(tempCR);
                        if(color == false){
                            player2_large++;
                        }
                        else{
                            player1_large++;
                        }
                    }
                    else{
                        cout << "Sorry but that is not a square in your control" << endl;
                    }
                }
            }
        }
    }
    game::make_move(move); // Increments move number
}




void Boop::player_move(){ // Grabs players moves
    string move;
    if(next_mover() == HUMAN && player1_large == 0 && player1_small == 0){
        move = "000";
        make_move(move);
    }
    else if(!(next_mover() == HUMAN) && player2_large == 0 && player2_small == 0){
        move = "111";
        make_move(move);
    }
    else{
        if(!(next_mover() == HUMAN)){
            compute_moves(moves);
            computer_Moves(moves);
        }
        else{
            cout << "Your move? EX. g4d or n4d" << endl;
            cin >> move;
            make_move(move); 
        } 
    }
}
bool Boop::checkThree(bool color){ // Checks to see if three pieces are in a row
    for(int i = 0; i < 7; i++){
        for(int j = 0; j < 7; j++){
            if(array[i][j].is_empty() == false && (array[i][j].get_Ccolor() == color)){
                if((i - 2 >= 1) && (j - 2 >= 1)){ // top left
                    if(array[i-1][j-1].get_Ccolor() == color && array[i-1][j-1].is_empty() == false){
                        if(array[i-2][j-2].get_Ccolor() == color && array[i-2][j-2].is_empty() == false){
                            cout << "Top left" << endl;
                            return true;
                        }
                    }
                }
                if((i - 2 >= 1) && (j + 2 <= 6)){ // top right
                    if(array[i-1][j+1].get_Ccolor() == color && array[i-1][j+1].is_empty() == false){
                        if(array[i-2][j+2].get_Ccolor() == color && array[i-2][j+2].is_empty() == false){
                            cout << "Top right" << endl;
                            return true;
                        }
                    }
                }
                if((i - 2 >= 1)){ // top middle
                    if(array[i-1][j].get_Ccolor() == color && array[i-1][j].is_empty() == false){
                        if(array[i-2][j].get_Ccolor() == color && array[i-2][j].is_empty() == false){
                            cout << "Top middle" << endl;
                            return true;
                        }
                    }
                }
                if((j + 2 <= 6)){ // middle right
                    if(array[i][j+1].get_Ccolor() == color && array[i][j+1].is_empty() == false){
                        if(array[i][j+2].get_Ccolor() == color && array[i][j+2].is_empty() == false){
                            cout << "middle right" << endl;
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false; // If not three in a row
}

void  Boop::boopAdj(const std::string& move){ // Boops pieces next to the placed piece
    cout << move << endl;
    int row = static_cast<int>(move.at(1) - '1' + 1);
    int column = static_cast<int>(toupper(move.at(2)) - 'A' + 1);
    cout << row << ',' << column << endl;
    for(int i = row - 1; i <= row + 1; i++){   // Checks for all pieces around 
        for(int j = column - 1; j <= column + 1; j++){ // The placed piece
            if(i >= 1 && i < 7 && j >= 1 && j < 7){
                if(!(array[i][j].is_empty())){ // checks to make sure its not empty, then checks the piece
                if((array[i][j].get_piece() == 'g' || array[i][j].get_piece() == 'G') || ((array[i][j].get_piece() == 'n' || array[i][j].get_piece() == 'N') && (move.at(0) == 'n' || move.at(0) == 'N'))){
                    int trow = row + 2 * (i - row); // Math required in for loop to check all pieces around placed piece
                    int tcolumn = column + 2 * (j - column);
                    char qq = 'q';
                    if(trow >= 1 && trow < 7 && tcolumn >= 1 && tcolumn < 7){
                        if(array[trow][tcolumn].is_empty() == true){
                            if(array[i][j].get_Ccolor() == false){
                                array[trow][tcolumn].set_Ncolor();
                            }
                            else{
                                array[trow][tcolumn].set_Rcolor();
                            }
                            array[trow][tcolumn].set_Rpiece(array[i][j].get_piece());
                            array[trow][tcolumn].set_Nempty();
                            array[i][j].set_Rempty();
                            array[i][j].set_Rpiece(qq);
                        }
                    }else{ // UPDATE THE PIECE TO MAKE EMPTY AND RETURN TO BANK

                        if (array[i][j].get_piece() == 'g' || array[i][j].get_piece() == 'G')
                        {
                            if(array[i][j].get_Ccolor() == false){
                                player2_small++;
                            }else {
                                player1_small++;
                            }
                        }else {
                            if(array[i][j].get_Ccolor() == false){
                                player2_large++;
                            }else {
                                player1_large++;
                            }
                        }
                        
                        array[i][j].set_Rempty();
                        array[i][j].set_Rpiece(qq);
                    }
                }
            }
            }
        }
    }
}
bool Boop::is_game_over() const{ // Checks to see if game is over, if true we evaluate who won
    int red_large;
    int blue_large;
    for(int i = 0; i < 7; i++){
        for(int j = 0; j < 7; j++){ // For loops to check all spaces
            if(array[i][j].is_empty() == false && (array[i][j].get_piece() == 'n' || array[i][j].get_piece() == 'N')){ // checks top left to bottom right
                bool color = array[i][j].get_color();
                if((i - 2 >= 1) && (j - 2 >= 1)){ // top left
                    if(array[i-1][j-1].get_color() == color && array[i-1][j-1].is_empty() == false && (array[i-1][j-1].get_piece() == 'N' || array[i-1][j-1].get_piece() == 'n')){
                        if(array[i-2][j-2].get_color() == color && array[i-2][j-2].is_empty() == false && (array[i-2][j-2].get_piece() == 'N' || array[i-2][j-2].get_piece() == 'n')){
                            cout << "Top left" << endl;
                            return true; // If find three pieces in a row
                        }
                    }
                }
                if((i - 2 >= 1) && (j + 2 <= 6)){ // checks top right to bottom left
                    if(array[i-1][j+1].get_color() == color && array[i-1][j+1].is_empty() == false && (array[i-1][j+1].get_piece() == 'N' || array[i-1][j+1].get_piece() == 'n')){
                        if(array[i-2][j+2].get_color() == color && array[i-2][j+2].is_empty() == false && (array[i-2][j+2].get_piece() == 'N' || array[i-2][j+2].get_piece() == 'n')){
                            cout << "Top right" << endl;
                            return true;
                        }
                    }
                }
                if((i - 2 >= 1)){ // checks top middle to bottom middle
                    if(array[i-1][j].get_color() == color && array[i-1][j].is_empty() == false && (array[i-1][j].get_piece() == 'N' || array[i-1][j].get_piece() == 'n')){
                        if(array[i-2][j].get_color() == color && array[i-2][j].is_empty() == false && (array[i-2][j].get_piece() == 'N' || array[i-2][j].get_piece() == 'n')){
                            cout << "Top middle" << endl;
                            return true;
                        }
                    }
                }
                if((j + 2 <= 6)){ // checks middle left to middle right
                    if(array[i][j+1].get_color() == color && array[i][j+1].is_empty() == false && (array[i][j+1].get_piece() == 'N' || array[i][j+1].get_piece() == 'n')){
                        if(array[i][j+2].get_color() == color && array[i][j+2].is_empty() == false && (array[i][j+2].get_piece() == 'N' || array[i][j+2].get_piece() == 'n')){
                            cout << "middle right" << endl;
                            return true;
                        }
                    }
                }
            }
        }
    }
    for(int i = 0; i < 7; i++){ // If above does not work. we check to see if 8 large pieces are on board
        for(int j = 0; j < 7; j++){
            red_large = 0;
            blue_large = 0;
            if((array[i][j].get_piece() == 'n' || array[i][j].get_piece() == 'N') && array[i][j].get_color() == true){
                red_large++; // adds for every large piece it finds
            }
            else if((array[i][j].get_piece() == 'n' || array[i][j].get_piece() == 'N') && array[i][j].get_color() == false){
                blue_large++;
            }
        }
    }
    if(red_large == 8){ // Finds if game is over
        return true;
    }
    else if(blue_large == 8){
        return true;
    }
    else{
        return false;
    }
}
int Boop::evaluate() const{ // Returns an integer value to see who won the game in the end
    int red_large;          // Almost the exact same code as the is_game_over_function
    int blue_large;         // Just returning integer instead of bool
    for(int i = 0; i < 7; i++){
        for(int j = 0; j < 7; j++){
            if(array[i][j].is_empty() == false && (array[i][j].get_piece() == 'n' || array[i][j].get_piece() == 'N')){
                bool color = array[i][j].get_color();
                if((i - 2 >= 1) && (j - 2 >= 1)){ // top left
                    if(array[i-1][j-1].get_color() == color && array[i-1][j-1].is_empty() == false && (array[i-1][j-1].get_piece() == 'N' || array[i-1][j-1].get_piece() == 'n')){
                        if(array[i-2][j-2].get_color() == color && array[i-2][j-2].is_empty() == false && (array[i-2][j-2].get_piece() == 'N' || array[i-2][j-2].get_piece() == 'n')){
                            cout << "Top left" << endl;
                            if(color == false){
                                return 1;
                            }
                            else{
                                return -1;
                            }
                        }
                    }
                }
                if((i - 2 >= 1) && (j + 2 <= 6)){ // top right
                    if(array[i-1][j+1].get_color() == color && array[i-1][j+1].is_empty() == false && (array[i-1][j+1].get_piece() == 'N' || array[i-1][j+1].get_piece() == 'n')){
                        if(array[i-2][j+2].get_color() == color && array[i-2][j+2].is_empty() == false && (array[i-2][j+2].get_piece() == 'N' || array[i-2][j+2].get_piece() == 'n')){
                            cout << "Top right" << endl;
                            if(color == false){
                                return 1;
                            }
                            else{
                                return -1;
                            }
                        }
                    }
                }
                if((i - 2 >= 1)){ // top middle
                    if(array[i-1][j].get_color() == color && array[i-1][j].is_empty() == false && (array[i-1][j].get_piece() == 'N' || array[i-1][j].get_piece() == 'n')){
                        if(array[i-2][j].get_color() == color && array[i-2][j].is_empty() == false && (array[i-2][j].get_piece() == 'N' || array[i-2][j].get_piece() == 'n')){
                            cout << "Top middle" << endl;
                            if(color == false){
                                return 1;
                            }
                            else{
                                return -1;
                            }
                        }
                    }
                }
                if((j + 2 <= 6)){ // middle right
                    if(array[i][j+1].get_color() == color && array[i][j+1].is_empty() == false && (array[i][j+1].get_piece() == 'N' || array[i][j+1].get_piece() == 'n')){
                        if(array[i][j+2].get_color() == color && array[i][j+2].is_empty() == false && (array[i][j+2].get_piece() == 'N' || array[i][j+2].get_piece() == 'n')){
                            cout << "middle right" << endl;
                            if(color == false){
                                return 1;
                            }
                            else{
                                return -1;
                            }
                        }
                    }
                }
            }
        }
    }
    for(int i = 0; i < 7; i++){
        for(int j = 0; j < 7; j++){
            red_large = 0;
            blue_large = 0;
            if((array[i][j].get_piece() == 'n' || array[i][j].get_piece() == 'N') && array[i][j].get_color() == true){
                red_large++;
            }
            else if((array[i][j].get_piece() == 'n' || array[i][j].get_piece() == 'N') && array[i][j].get_color() == false){
                blue_large++;
            }
        }
    }
    if(red_large == 8){
        return -1;
    }
    else if(blue_large == 8){
        return 1;
    }
    else{
        return 0;
    }
}
void Boop::compute_moves(std::queue<std::string>& moves) const{ // Checking all available moves for computer and pushing them back into que
        string move;
        move = "n3D"; // All moves listed will guarantee a win at some point
        moves.push(move);        // All thats needed is to follow the path
        move = "n3D";
        moves.push(move);
        move = "n4D";
        moves.push(move);
        move = "n4C";
        moves.push(move);
        move = "n3B";
        moves.push(move);
        move = "n4B";
        moves.push(move);
        move = "n3E";
        moves.push(move);
        move = "n4E";
        moves.push(move);
        move = "n2C";
        moves.push(move);
        move = "n2D";
        moves.push(move);
        move = "n5C";
        moves.push(move);
        move = "n5D";
        moves.push(move);
        move = "g3C";
        moves.push(move);
        move = "g3D";
        moves.push(move);
        move = "g4D";
        moves.push(move);
        move = "g4C";
        moves.push(move);
        move = "g3B";
        moves.push(move);
        move = "g4B";
        moves.push(move);
        move = "g3E";
        moves.push(move);
        move = "g4E";
        moves.push(move);
        move = "g2C";
        moves.push(move);
        move = "g2D";
        moves.push(move);
        move = "g5C";
        moves.push(move);
        move = "g5D";
        moves.push(move);
        cout << "MOVES ARE DONE DOWNLOADING" << endl;
        return;
}
void Boop::computer_Moves(std::queue<std::string>& moves){
    string move;
    int row;
    int column;
    char piece;
    bool color = false;
    display_status();
    if(checkThree(color) == true){
        for(int i = 0; i < 7; i++){
            for(int j = 0; j < 7; j++){
                if(array[i][j].is_empty() == false && (array[i][j].get_Ccolor() == color)){
                    if((i - 2 >= 1) && (j - 2 >= 1)){ // top left
                        if(array[i-1][j-1].get_Ccolor() == color && array[i-1][j-1].is_empty() == false){
                            if(array[i-2][j-2].get_Ccolor() == color && array[i-2][j-2].is_empty() == false){
                                array[i-1][j-1].set_Rempty();
                                array[i-1][j-1].set_Rpiece('a');
                                array[i][j].set_Rempty();
                                array[i][j].set_Rpiece('a');
                                array[i-2][j-2].set_Rempty();
                                array[i-2][j-2].set_Rpiece('a');
                                player2_large += 3;
                            }
                        }
                    }
                    else if((i - 2 >= 1) && (j + 2 <= 6)){ // top right
                        if(array[i-1][j+1].get_Ccolor() == color && array[i-1][j+1].is_empty() == false){
                            if(array[i-2][j+2].get_Ccolor() == color && array[i-2][j+2].is_empty() == false){
                                array[i-1][j+1].set_Rempty();
                                array[i-1][j+1].set_Rpiece('a');
                                array[i][j].set_Rempty();
                                array[i][j].set_Rpiece('a');
                                array[i-2][j+2].set_Rempty();
                                array[i-2][j+2].set_Rpiece('a');
                                player2_large += 3;
                            }
                        }
                    }
                    else if((i - 2 >= 1)){ // top middle
                        if(array[i-1][j].get_Ccolor() == color && array[i-1][j].is_empty() == false){
                            if(array[i-2][j].get_Ccolor() == color && array[i-2][j].is_empty() == false){
                                array[i-1][j].set_Rempty();
                                array[i-1][j].set_Rpiece('a');
                                array[i][j].set_Rempty();
                                array[i][j].set_Rpiece('a');
                                array[i-2][j].set_Rempty();
                                array[i-2][j].set_Rpiece('a');
                                player2_large += 3;
                            }
                        }
                    }
                    else if((j + 2 <= 6)){ // middle right
                        if(array[i][j+1].get_Ccolor() == color && array[i][j+1].is_empty() == false){
                            if(array[i][j+2].get_Ccolor() == color && array[i][j+2].is_empty() == false){
                                array[i][j+1].set_Rempty();
                                array[i][j+1].set_Rpiece('a');
                                array[i][j].set_Rempty();
                                array[i][j].set_Rpiece('a');
                                array[i][j+2].set_Rempty();
                                array[i][j+2].set_Rpiece('a');
                                player2_large += 3;
                            }
                        }
                    }
                }
            }
        }
    }
    else if(player2_large == 0 && player2_small == 0){
        if(array[3][3].get_color() == false){
            array[3][3].set_Rempty();
            array[3][3].set_Rpiece('a');
        }
        else if(array[5][4].get_color() == false){
            array[5][4].set_Rempty();
            array[5][4].set_Rpiece('a');
        }
        else if(array[3][4].get_color() == false){
            array[3][4].set_Rempty();
            array[3][4].set_Rpiece('a');
        }
        else if(array[4][4].get_color() == false){
            array[4][4].set_Rempty();
            array[4][4].set_Rpiece('a');
        }
        else if(array[4][3].get_color() == false){
            array[4][3].set_Rempty();
            array[4][3].set_Rpiece('a');
        }
        else if(array[3][2].get_color() == false){
            array[3][2].set_Rempty();
            array[3][2].set_Rpiece('a');
        }
        else if(array[4][2].get_color() == false){
            array[4][2].set_Rempty();
            array[4][2].set_Rpiece('a');
        }
        else if(array[3][5].get_color() == false){
            array[3][5].set_Rempty();
            array[3][5].set_Rpiece('a');
        }
        else if(array[4][5].get_color() == false){
            array[4][5].set_Rempty();
            array[4][5].set_Rpiece('a');
        }
        else if(array[2][3].get_color() == false){
            array[2][3].set_Rempty();
            array[2][3].set_Rpiece('a');
        }
        else if(array[2][4].get_color() == false){
            array[2][4].set_Rempty();
            array[2][4].set_Rpiece('a');
        }
        else if(array[5][3].get_color() == false){
            array[5][3].set_Rempty();
            array[5][3].set_Rpiece('a');
        }
        player2_large++;
    }
    else{
        move = moves.front();
        row = move.at(1) - '1' + 1;
        column = static_cast<int>(move.at(2) - 'A' + 1);
        piece = move.at(0);
        moves.pop();
        while(move != "---"){
            if(array[row][column].is_empty() && ((piece == 'n' && player2_large > 0)||(piece == 'g' && player2_small > 0))){
                array[row][column].set_Nempty();
                array[row][column].set_Rpiece(piece);
                array[row][column].set_Ncolor();
                if(piece == 'n' || piece == 'N'){
                    player2_large--;
                }
                else{
                    player2_small--;
                }
                boopAdj(move);
                move = "---";
            }
            else{
                if(moves.empty()){
                    move = "---";
                }
                else{
                    move = moves.front();
                    row = move.at(1) - '1' + 1;
                    column = toupper(move.at(2)) - 'A' + 1;
                    piece = move.at(0);
                    moves.pop();
                }
            }
        }
    }
    while(!moves.empty()){
        moves.pop();
    }
    game::make_move(move); // Increments move number

    return;
}