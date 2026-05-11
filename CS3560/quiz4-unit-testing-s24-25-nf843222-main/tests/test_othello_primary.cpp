/**
 * @file
 * @author Krerkkiat Chusap
 * @brief Test cases for primary functions of Othello.
 * 
*/
#include <string>
#include <vector>

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_all.hpp>

#include <othello.hpp>
#include <utils.hpp>

using namespace std;

SCENARIO("primary functions should work") {
    GIVEN("a starting board") {
        Othello o;
        o.restart();

        THEN("1st out of the four starting moves should work") {
            vector<string> expected_board = {"--------",
                                             "--------",
                                             "---x----",
                                             "---xx---",
                                             "---xo---",
                                             "--------",
                                             "--------",
                                             "--------"};

            o.make_move("d3");
            REQUIRE(o.get_board_as_string() == unlines(expected_board));
        }

        THEN("2nd out of the four starting moves should work") {
            vector<string> expected_board = {"--------",
                                             "--------",
                                             "--------",
                                             "--xxx---",
                                             "---xo---",
                                             "--------",
                                             "--------",
                                             "--------"};

            o.make_move("c4");
            REQUIRE(o.get_board_as_string() == unlines(expected_board));
        }

        THEN("3rd out of the four starting moves should work") {
            vector<string> expected_board = {"--------",
                                             "--------",
                                             "--------",
                                             "---ox---",
                                             "---xxx--",
                                             "--------",
                                             "--------",
                                             "--------"};

            o.make_move("f5");
            REQUIRE(o.get_board_as_string() == unlines(expected_board));
        }

        THEN("4th out of the four starting moves should work") {
            vector<string> expected_board = {"--------",
                                             "--------",
                                             "--------",
                                             "---ox---",
                                             "---xx---",
                                             "----x---",
                                             "--------",
                                             "--------"};

            o.make_move("e6");
            REQUIRE(o.get_board_as_string() == unlines(expected_board));
        }
    }
}