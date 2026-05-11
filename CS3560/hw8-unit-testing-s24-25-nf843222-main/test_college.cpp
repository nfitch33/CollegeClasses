/**
 * @file
 * @author Nathaniel Fitch
 *
 **/

// STEP 6 - The include statements
// YOUR_ANSWER_HERE
#include <catch2/catch_test_macros.hpp>
#include "college.hpp"
#include <catch2/matchers/catch_matchers_floating_point.hpp>

// STEP 6 - The using namespace statements.
// YOUR_ANSWER_HERE
using namespace Catch;
using namespace Catch::Matchers;

// STEP 6 - The simple TEST_CASE macro
// YOUR_ANSWER_HERE
TEST_CASE("hours of no classes must be 0"){
    College college = College("Ohio University");
    CHECK(college.get_college_name() == "Ohio University");
    REQUIRE_THAT(college.hours(), WithinAbs(0.0, 0.001));
}


// STEP 7 - Your test cases for College::gpa().
// YOUR_ANSWER_HERE


TEST_CASE("No classes so GPA is 0.0"){
    Course Computers;
    College GPA = College("0.0");
    Computers.set_course("3560", "F", 0.0);
    GPA.add(Computers);
    CHECK(GPA.hours() == 0.0);
}

TEST_CASE("Not there yet GPA 0.0"){
    Course Science;
    College GPA = College("0.0");
    Science.set_course("2100", "F", 0.0);
    GPA.add(Science);
    CHECK(GPA.hours() == 0.0);
}
TEST_CASE("Have GPA 4.0?"){
    Course Health;
    College GPA = College("4.0");
    Health.set_course("1500", "A+", 4.0);
    GPA.add(Health);
    CHECK(GPA.hours() == 4.0);
}
TEST_CASE("GPA is 4.0"){
    Course Engineering;
    College GPA = College("4.0");
    Engineering.set_course("1100", "A", 4.0);
    GPA.add(Engineering);
    CHECK(GPA.hours() == 4.0);
}