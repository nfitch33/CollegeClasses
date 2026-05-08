/***********************************************
 *
 *	Test cases for CS2401 Lab 12, Recursion
 *	Made by Kyle Chiasson, kc428921@ohio.edu
 *	Last updated 3/18/2024
 *	For automatic grading to work, do not change this file.
 *	Students are encouraged to read through to understand project requirements, however.
 *
 * ********************************************/

#define CATCH_CONFIG_MAIN
#include <iostream>
#include <sstream>
#include "catch.hpp"
#include "../recursion.h"

static std::streambuf *coutbuf = std::cout.rdbuf();

TEST_CASE("Counting"){
	SECTION("Small Even"){
		std::stringstream oss;
		std::cout.rdbuf(oss.rdbuf());
		counting(4);
		std::cout.rdbuf(coutbuf);
		REQUIRE(oss.str() == "0\n2\n4\n");
	}
	SECTION("Small Odd"){
		std::stringstream oss;
		std::cout.rdbuf(oss.rdbuf());
		counting(5);
		std::cout.rdbuf(coutbuf);
		REQUIRE(oss.str() == "0\n2\n4\n");
	}
	SECTION("Large Even"){
		std::stringstream oss;
		std::cout.rdbuf(oss.rdbuf());
		counting(20);
		std::cout.rdbuf(coutbuf);
		REQUIRE(oss.str() == "0\n2\n4\n6\n8\n10\n12\n14\n16\n18\n20\n");
	}
	SECTION("Large Odd"){
		std::stringstream oss;
		std::cout.rdbuf(oss.rdbuf());
		counting(21);
		std::cout.rdbuf(coutbuf);
		REQUIRE(oss.str() == "0\n2\n4\n6\n8\n10\n12\n14\n16\n18\n20\n");
	}
	SECTION("Zero"){
		std::stringstream oss;
		std::cout.rdbuf(oss.rdbuf());
		counting(0);
		std::cout.rdbuf(coutbuf);
		REQUIRE(oss.str() == "0\n");
	}
}
TEST_CASE("Reversing"){
	SECTION("Numbers: Whole"){
		std::string s = "01234";
		reversing(s, 0, 4);
		REQUIRE(s == "43210");
	}
	SECTION("Numbers: Part"){
		std::string s = "01234";
		reversing(s, 2, 4);
		REQUIRE(s == "01432");
	}
	SECTION("Sentance"){
		std::string s = "Ohio University department of electrical engineering and computer science.";
		reversing(s, 16, 25);
		REQUIRE(s == "Ohio University tnemtraped of electrical engineering and computer science.");
	}
}
TEST_CASE("Footer"){
	SECTION("Score") {
		std::cout << "\e[34m===============================================================================\e[0m\n";
		std::cout << "FOR ALL ERROR MESSAGES, THE FIRST VALUE IS THE ONE PROVIDED BY THE CLASS,\nAND THE SECOND VALUE IS THE DESIRED OUTPUT.\nSTART AT THE TOP AND WORK DOWNWARDS\n";
		std::cout << "\e[34m===============================================================================\e[0m\n";
	}
}