/***********************************************
 *
 *	Test cases for CS2401 Lab 1, Operator Overloading
 *	Made by Kyle Chiasson, kc428921@ohio.edu
 *	Last updated 01/22/2024
 *	For automatic grading to work, do not change this file.
 *	Students are encouraged to read through to understand project requirements, however.
 *
 * ********************************************/
#define CATCH_CONFIG_MAIN
#include <fstream>
#include <sstream>
#include "../MyTime.h"
#include "catch.hpp"

static int score = 0;

TEST_CASE("Testing Overloaded Operators") {
	std::stringstream stream;
	MyTime t1;
	MyTime t2(3, 15);
	MyTime t3(0, 0);
	MyTime t4(7, 50);
	SECTION("Test Constructors") {
		stream << t1;
		CHECK(stream.str() == "0:00");
		stream.str("");

		stream << t2;
		CHECK(stream.str() == "3:15");
		stream.str("");

		score += 1;
	}
	SECTION("Test Input"){
		MyTime t5;
		stream << "7:50";
		stream >> t5;
		CHECK(t5 == t4);
		stream.str("");

		score += 1;
	}
	SECTION("Test Addition"){
		stream << t1 + t2;
		CHECK(stream.str() == "3:15");
		stream.str("");

		stream << t2 + t4;
		CHECK(stream.str() == "11:05");
		stream.str("");

		score += 1;
	}
	SECTION("Test Subtraction"){
		stream << t2 - t1;
		CHECK(stream.str() == "3:15");
		stream.str("");

		stream << t4 - t2;
		CHECK(stream.str() == "4:35");
		stream.str("");

		score += 1;
	}
	SECTION("Test Multiplication"){
		stream << t1 * 5;
		CHECK(stream.str() == "0:00");
		stream.str("");

		stream << t2 * 5;
		CHECK(stream.str() == "16:15");
		stream.str("");

		score += 1;
	}
	SECTION("Test Division"){
		stream << t1 / 5;
		CHECK(stream.str() == "0:00");
		stream.str("");

		stream << t2 / 5;
		CHECK(stream.str() == "0:39");
		stream.str("");

		score += 1;
	}
	SECTION("Test Comparisons"){
		stream << (t1 < t3);
		CHECK(stream.str() == "0");
		stream.str("");

		stream << (t2 < t4);
		CHECK(stream.str() == "1");
		stream.str("");

		stream << (t1 <= t3);
		CHECK(stream.str() == "1");
		stream.str("");

		stream << (t2 <= t4);
		CHECK(stream.str() == "1");
		stream.str("");

		stream << (t1 == t3);
		CHECK(stream.str() == "1");
		stream.str("");

		stream << (t2 == t4);
		CHECK(stream.str() == "0");
		stream.str("");

		score += 1;
	}
	SECTION("Score") {
		std::cout << "FOR ALL ERROR MESSAGES, THE FIRST VALUE IS THE ONE PROVIDED BY THE CLASS,\nAND THE SECOND VALUE IS THE DESIRED OUTPUT.\n";
		std::cout << "START AT THE TOP AND WORK DOWNWARDS\n";
		std::cout << "Score: " << score << " / 7\n";
	}
}

