/***********************************************
 *
 *	Test cases for CS2401 Lab 5, Linked Lists
 *	Made by Kyle Chiasson, kc428921@ohio.edu
 *	Last updated 2/12/2024
 *	For automatic grading to work, do not change this file.
 *	Students are encouraged to read through to understand project requirements, however.
 *
 * ********************************************/
#define CATCH_CONFIG_MAIN
#include <fstream>
#include <sstream>
#include "../list.h"
#include "catch.hpp"

//Note: These test cases require you to not change the given code
TEST_CASE("Search"){
	Lilist ll;
	ll.add("Kyle");
	ll.add("Luke");
	ll.add("Will");
	ll.add("Zach");
	ll.add("Matthew");
	SECTION("In List"){
		REQUIRE_FALSE(ll.search("Zach") == nullptr);
	}
	SECTION("Not In List"){
		REQUIRE(ll.search("Noah") == nullptr);
	}
}
TEST_CASE("Front To Back"){
	SECTION("Move"){
		Lilist ll;
		std::stringstream o;
		ll.add("Kyle");
		ll.add("Luke");
		ll.add("Will");
		ll.add("Zach");
		ll.add("Matthew");
		ll.move_front_to_back();
		ll.move_front_to_back();
		std::streambuf *coutbuf = std::cout.rdbuf();
		std::cout.rdbuf(o.rdbuf());
		ll.show();
		std::cout.rdbuf(coutbuf);
		REQUIRE(o.str() == "Will Zach Matthew Kyle Luke \n");
	}
}
TEST_CASE("Footer"){
	SECTION("Score") {
		std::cout << "\e[34m===============================================================================\e[0m\n";
		std::cout << "FOR ALL ERROR MESSAGES, THE FIRST VALUE IS THE ONE PROVIDED BY THE CLASS,\nAND THE SECOND VALUE IS THE DESIRED OUTPUT.\nSTART AT THE TOP AND WORK DOWNWARDS\n";
		std::cout << "\e[34m===============================================================================\e[0m\n";
	}
}