/**
 * @file
 * @author Nathaniel Fitch
 * 
*/
#include <string>
#include <vector>
#include <othello.hpp>
#include <game.hpp>
#include <utils.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_all.hpp>

// YOUR ANSWER
TEST_CASE("Checks if white has a single point on the board (First move)"){
    Othello o;
    o.make_move("d3");
    CHECK(o.evaluate() == 1);
}

TEST_CASE("Checks that moves made will update the evaluate function"){
    Othello o;
    Othello x;
    o.make_move("d3");
    x.make_move("d4");
    o.make_move("a2");
    x.make_move("a3");
    o.make_move("b2");
    CHECK(o.evaluate() > x.evaluate());
    x.make_move("b3");
    o.make_move("d5");
    x.make_move("b4");
    x.make_move("c2");
    CHECK(x.evaluate() > o.evaluate());
}

//This is used to show that pieces captured change point differences
TEST_CASE("Evaluates if O (white) piece is surrounded and became X (black piece)"){
    Othello o;
    o.make_move("a1");
    o.make_move("b1");
    o.make_move("b2");
    o.make_move("a4");
    o.display_status();
    o.make_move("c1");
    o.display_status();
    o.make_move("a5");
    o.make_move("a3");
    o.display_status();
    CHECK(o.evaluate() == 1); // will jump between 1 and -1 and never be 0 anymore since a piece was captured and someone will win
    o.make_move("d4");
    CHECK(o.evaluate() == -1); // same as line 50 comment
    o.make_move("b4");
    o.make_move("e4");
    o.make_move("b5");
    o.make_move("e5");
    o.make_move("a6");
    o.display_status();
    CHECK(o.evaluate() == 1); // Shows black will win but final few moves will show a bug
    o.make_move("a7");
    CHECK(o.evaluate() == -1);  // These final two lines show that there is a bug with the actual game, when capturing a piece, you should add more to their point total
                                    // -- Laws of the game othello.
}