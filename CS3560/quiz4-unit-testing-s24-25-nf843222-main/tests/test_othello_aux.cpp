/**
 * @file
 * @author Krerkkiat Chusap
 * @brief Test cases for the auxiliary functions
 * 
*/
#include <string>
#include <vector>

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_all.hpp>

#include <othello.hpp>
#include <utils.hpp>

using namespace std;

SCENARIO("auxiliary functions should work") {
    GIVEN("a starting board") {
        Othello o;
        o.restart();

        THEN("the get_board should be working") {
            vector<string>  expected_board = {"--------",
                                              "--------",
                                              "--------",
                                              "---ox---",
                                              "---xo---",
                                              "--------",
                                              "--------",
                                              "--------"};
            // o.display_status();
            // REQUIRE(false);
            REQUIRE(o.get_board_as_string() == unlines(expected_board));
        }
    }

    GIVEN("a string 1 as board") {
        vector<string> starting_board = {"--------",
                                         "--------",
                                         "--------",
                                         "---ox---",
                                         "---xo---",
                                         "--------",
                                         "--------",
                                         "--------"};
        Othello o(starting_board);

        THEN("constructor should work") {
            string expected_board = "--------\n--------\n--------\n---ox---\n---xo---\n--------\n--------\n--------\n";
            // o.display_status();
            // REQUIRE(false);
            REQUIRE(o.get_board_as_string() == expected_board);
        }
    }

    GIVEN("a string 2 as board") {
        vector<string> starting_board = {"x-------",
                                         "-------o",
                                         "--------",
                                         "---ox---",
                                         "---xo---",
                                         "oox-----",
                                         "--------",
                                         "-----xxo"};
        Othello o(starting_board);

        THEN("constructor should work") {
            string expected_board = "x-------\n-------o\n--------\n---ox---\n---xo---\noox-----\n--------\n-----xxo\n";
            // o.display_status();
            // REQUIRE(false);
            REQUIRE(o.get_board_as_string() == expected_board);
        }
    }

    GIVEN("a string 2 (but unlines) as board") {
        // So we can test the constructor for multi-line string.
        vector<string> starting_board = {"x-------",
                                         "-------o",
                                         "--------",
                                         "---ox---",
                                         "---xo---",
                                         "oox-----",
                                         "--------",
                                         "-----xxo"};
        Othello o(unlines(starting_board));

        THEN("constructor should work") {
            string expected_board = "x-------\n-------o\n--------\n---ox---\n---xo---\noox-----\n--------\n-----xxo\n";
            // o.display_status();
            // REQUIRE(false);
            REQUIRE(o.get_board_as_string() == expected_board);
        }
    }
}