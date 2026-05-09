/**
 * @author Nathaniel Fitch
 */

// YOUR_ANSWER: Include statements
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "functions.hpp"
// YOUR_ANSWER: Using namespace statement(s)
using namespace Catch;
using namespace Catch::Matchers;

// YOUR_ANSWER: TEST CASE 1
TEST_CASE("Checking countLine for 1st file"){
    int line = 1
    CHECK(countLine(input1.txt) == 1);
    REQUIRE_THAT(line == countLine(input1.txt));
}

// YOUR_ANSWER: TEST CASE 2
TEST_CASE("checking input 5 file"){
    int line = 6;
    CHECK(countChar(input5.txt) == 6);
    REQUIRE_THAT(line == countChar(input5.txt));
}