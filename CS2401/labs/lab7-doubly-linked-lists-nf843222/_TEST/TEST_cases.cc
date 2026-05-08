/***********************************************
 *
 *	Test cases for CS2401 Lab 7, Doubly Linked List
 *	Made by Kyle Chiasson, kc428921@ohio.edu
 *	Last updated 2/22/2024
 *	For automatic grading to work, do not change this file.
 *	Students are encouraged to read through to understand project requirements, however.
 *
 * ********************************************/

#define CATCH_CONFIG_MAIN
#include <iostream>
#include <sstream>
#include <vector>
#include "catch.hpp"
#include "../llist.h"

static std::streambuf *coutbuf = std::cout.rdbuf();

std::stringstream FrontStream(LList ll){
	std::stringstream s;
	std::cout.rdbuf(s.rdbuf());
	ll.frontview();
	std::cout.rdbuf(coutbuf);
	return s;
}
std::stringstream RearStream(LList ll){
	std::stringstream s;
	std::cout.rdbuf(s.rdbuf());
	ll.rearview();
	std::cout.rdbuf(coutbuf);
	return s;
}
bool FrontIsBack(LList ll){
	int temp;
	std::stringstream f = FrontStream(ll), r = RearStream(ll);
	std::vector<int> fv, rv;
	for(f >> temp; !f.eof(); f >> temp)
		fv.push_back(temp);
	for(r >> temp; !r.eof(); r >> temp)
		rv.push_back(temp);
	std::reverse(rv.begin(), rv.end());
	return rv == fv;
}

TEST_CASE("Add"){
	SECTION("Normal"){
		LList ll;
		ll.add_item(2);
		ll.add_item(4);
		ll.add_item(6);
		ll.add_item(8);
		ll.add_item(1);
		ll.add_item(3);
		ll.add_item(5);
		ll.add_item(7);
		ll.add_item(0);
		ll.add_item(9);
		std::stringstream l = FrontStream(ll);
		REQUIRE(l.str() == "2  4  6  5  0  8  1  3  7  9  \n");
	}
}
TEST_CASE("Rearview"){
	SECTION("Normal"){
		LList ll;
		ll.add_item(2);
		ll.add_item(4);
		ll.add_item(6);
		ll.add_item(8);
		ll.add_item(1);
		ll.add_item(3);
		ll.add_item(5);
		ll.add_item(7);
		ll.add_item(0);
		ll.add_item(9);
		REQUIRE(FrontIsBack(ll));
	}
}
//make sure both front and back look good and to edit the original after coppying
TEST_CASE("Copy Constructor"){
	SECTION("Empty"){
		LList ll1;
		LList ll2(ll1);
		ll1.add_item(9);
		REQUIRE(FrontIsBack(ll2));
	}
	SECTION("One"){
		LList ll1;
		ll1.add_item(2);
		LList ll2(ll1);
		ll1.add_item(9);
		REQUIRE(FrontIsBack(ll2));
	}
	SECTION("Many"){
		LList ll1;
		ll1.add_item(2);
		ll1.add_item(4);
		ll1.add_item(6);
		ll1.add_item(8);
		ll1.add_item(1);
		ll1.add_item(3);
		ll1.add_item(5);
		ll1.add_item(7);
		ll1.add_item(0);
		ll1.add_item(9);
		LList ll2(ll1);
		ll1.add_item(9);
		REQUIRE(FrontIsBack(ll2));
	}
}
TEST_CASE("Footer"){
	SECTION("Score") {
		std::cout << "\e[34m===============================================================================\e[0m\n";
		std::cout << "FOR ALL ERROR MESSAGES, THE FIRST VALUE IS THE ONE PROVIDED BY THE CLASS,\nAND THE SECOND VALUE IS THE DESIRED OUTPUT.\nSTART AT THE TOP AND WORK DOWNWARDS\n";
		std::cout << "\e[34m===============================================================================\e[0m\n";
	}
}