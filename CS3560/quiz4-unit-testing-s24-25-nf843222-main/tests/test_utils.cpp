/**
 * @file
 * @author Krerkkiat Chusap
 * @brief Test cases for the utility functions.
*/
#include <string>
#include <vector>

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_all.hpp>

#include <utils.hpp>

using namespace std;

TEST_CASE( "split_by with 1-char delimiter is correct", "[split-by][functions]" ) {
    // Preparation.
    string value = "email_handle,PID,codewar_username,github_username";

    // Perform the task.
    vector<string> result = split_by(value, ",");

    // Check the result.
    vector<string> expected_result = {"email_handle", "PID", "codewar_username", "github_username"};

    REQUIRE( expected_result == result );
}

TEST_CASE( "split_by with 2-char delimiter is correct", "[split-by]" ) {
    // Preparation.
    string value = "email_handle::PID::codewar_username::github_username";

    // Perform the task.
    vector<string> result = split_by(value, "::");

    // Check the result.
    vector<string> expected_result = {"email_handle", "PID", "codewar_username", "github_username"};

    REQUIRE( expected_result == result );
}

TEST_CASE("unlines of nothing should be empty string", "[split-by]") {
    vector<string> lines;
    string result = unlines(lines);
    REQUIRE(result == "");
}

TEST_CASE("unlines of some lines should work", "[split-by]") {
    vector<string> lines = {"123", "456"};
    string result = unlines(lines);
    REQUIRE(result == "123\n456\n");
}