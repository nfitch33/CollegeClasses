/***********************************************
 *
 *	Test cases for CS2401 Lab 8, Templates
 *	Made by Kyle Chiasson, kc428921@ohio.edu
 *	Last updated 3/15/2024
 *	For automatic grading to work, do not change this file.
 *	Students are encouraged to read through to understand project requirements, however.
 *
 * ********************************************/

#define CATCH_CONFIG_MAIN
#include <iostream>
#include <sstream>
#include "catch.hpp"
#include "../tarray.h"

TEST_CASE("Add"){
	SECTION("Int"){
		Tarray<int> intArr;
		intArr.add(0);
		intArr.add(1);
		intArr.add(2);
		intArr.add(3);
		intArr.add(4);
		std::stringstream ss;
		for(intArr.start(); intArr.is_item(); intArr.advance())
			ss << intArr.current() << ' ';
		REQUIRE(ss.str() == "0 1 2 3 4 ");
	}
	SECTION("String"){
		Tarray<std::string> strArr;
		strArr.add("zero");
		strArr.add("one");
		strArr.add("two");
		strArr.add("three");
		strArr.add("four");
		std::stringstream ss;
		for(strArr.start(); strArr.is_item(); strArr.advance())
			ss << strArr.current() << ' ';
		REQUIRE(ss.str() == "zero one two three four ");
	}
}
TEST_CASE("Removal In List"){
	SECTION("Int"){
		Tarray<int> intArr;
		intArr.add(0);
		intArr.add(1);
		intArr.add(2);
		intArr.add(3);
		intArr.add(4);

		intArr.start();
		for(int i = 0; i < 2; i++)
			intArr.advance();
		intArr.remove_current();

		std::stringstream ss;
		for(intArr.start(); intArr.is_item(); intArr.advance())
			ss << intArr.current() << ' ';
		REQUIRE(ss.str() == "0 1 3 4 ");
	}
	SECTION("String"){
		Tarray<std::string> strArr;
		strArr.add("zero");
		strArr.add("one");
		strArr.add("two");
		strArr.add("three");
		strArr.add("four");

		strArr.start();
		for(int i = 0; i < 2; i++)
			strArr.advance();
		strArr.remove_current();

		std::stringstream ss;
		for(strArr.start(); strArr.is_item(); strArr.advance())
			ss << strArr.current() << ' ';
		REQUIRE(ss.str() == "zero one three four ");
	}
}
TEST_CASE("Removal Out Of List"){
	SECTION("Int"){
		Tarray<int> intArr;
		intArr.add(0);
		intArr.add(1);
		intArr.add(2);
		intArr.add(3);
		intArr.add(4);

		intArr.start();
		for(int i = 0; i < 6; i++)
			intArr.advance();
		intArr.remove_current();

		std::stringstream ss;
		for(intArr.start(); intArr.is_item(); intArr.advance())
			ss << intArr.current() << ' ';

		REQUIRE(ss.str() == "0 1 2 3 4 ");
	}
	SECTION("String"){
		Tarray<std::string> strArr;
		strArr.add("zero");
		strArr.add("one");
		strArr.add("two");
		strArr.add("three");
		strArr.add("four");

		strArr.start();
		for(int i = 0; i < 6; i++)
			strArr.advance();
		strArr.remove_current();

		std::stringstream ss;
		for(strArr.start(); strArr.is_item(); strArr.advance())
			ss << strArr.current() << ' ';
		REQUIRE(ss.str() == "zero one two three four ");
	}
}
TEST_CASE("Footer"){
	SECTION("Score") {
		std::cout << "\e[34m===============================================================================\e[0m\n";
		std::cout << "FOR ALL ERROR MESSAGES, THE FIRST VALUE IS THE ONE PROVIDED BY THE CLASS,\nAND THE SECOND VALUE IS THE DESIRED OUTPUT.\nSTART AT THE TOP AND WORK DOWNWARDS\n";
		std::cout << "\e[34m===============================================================================\e[0m\n";
	}
}