/***********************************************
 *
 *	Test cases for CS2401 Lab 11, Stacks and Queues
 *	Made by Kyle Chiasson, kc428921@ohio.edu
 *	Last updated 4/3/2024
 *	For automatic grading to work, do not change this file.
 *	Students are encouraged to read through to understand project requirements, however.
 *
 * ********************************************/

#define CATCH_CONFIG_MAIN
#include <iostream>
#include <sstream>
#include "catch.hpp"
#include "../queue.h"
#include "../stack.h"

TEST_CASE("Stack"){
	SECTION("First"){
		std::stringstream iss("12 679 5 + 4 * 8 / +\n"), oss;
		EvaluateExpression(iss, oss);
		REQUIRE(oss.str() == "Result: 354\n");
	}
	SECTION("Second"){
		std::stringstream iss("34 6 + 16 * 18 -\n"), oss;
		EvaluateExpression(iss, oss);
		REQUIRE(oss.str() == "Result: 622\n");
	}
	SECTION("Third"){
		std::stringstream iss("12 6 - 8 + 7 * +\n"), oss;
		EvaluateExpression(iss, oss);
		REQUIRE(oss.str() == "Error: Expression doesn't contain enough numbers.\n");
	}
	SECTION("Fourth"){
		std::stringstream iss("56 78 84 + 33 *\n"), oss;
		EvaluateExpression(iss, oss);
		REQUIRE(oss.str() == "Error: Incorrect amount of numbers entered.\n");
	}
}
TEST_CASE("Queue"){
	SECTION("Chore I/O"){
		std::stringstream iss("Stuff\n1\n"), oss;
		Chore c;
		c.input(iss);
		c.output(oss);
		REQUIRE(oss.str() == iss.str());
	}
	SECTION("Chore <"){
		std::stringstream iss1("Stuff\n1\n"), iss2("Stuff\n2\n");
		Chore c1, c2;
		c1.input(iss1);
		c2.input(iss2);
		REQUIRE(c1 < c2);
		REQUIRE_FALSE(c2 < c1);
		REQUIRE_FALSE(c1 < c1);
	}
	SECTION("Queues"){
		std::stringstream iss("A\n4\nB\n2\nC\n1\nD\n5\nE\n3\n"), oss;
		GetFiveChores(iss, oss);
		REQUIRE(oss.str() == "Outputting Queue:\nA\n4\nB\n2\nC\n1\nD\n5\nE\n3\nOutputting Priority Queue:\nD\n5\nA\n4\nE\n3\nB\n2\nC\n1\n");
	}
}
TEST_CASE("Footer"){
	SECTION("Score") {
		std::cout << "\e[34m===============================================================================\e[0m\n";
		std::cout << "FOR ALL ERROR MESSAGES, THE FIRST VALUE IS THE ONE PROVIDED BY THE CLASS,\nAND THE SECOND VALUE IS THE DESIRED OUTPUT.\nSTART AT THE TOP AND WORK DOWNWARDS\n";
		std::cout << "\e[34m===============================================================================\e[0m\n";
	}
}