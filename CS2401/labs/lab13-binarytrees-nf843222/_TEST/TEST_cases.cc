/***********************************************
 *
 *	Test cases for CS2401 Lab 13, Binary Trees
 *	Made by Kyle Chiasson, kc428921@ohio.edu
 *	Last updated 4/9/2024
 *	For automatic grading to work, do not change this file.
 *	Students are encouraged to read through to understand project requirements, however.
 *
 * ********************************************/

#define CATCH_CONFIG_MAIN
#include <iostream>
#include <sstream>
#include "catch.hpp"
#include "../btreelab.h"

static std::streambuf *coutbuf = std::cout.rdbuf();

//This is the file the students are given but as a string
static std::string file = "Kevin\nBilly\nWilliam\nAli\nColleen\nJessica\nMatthew\nSamantha\nChris\nBenjamin\nCasey\nMeghan\nEvan\nLydia\nAlex\nNicholas\nLuke\nNicholas\nWaylon\nRobert\nJeffrey\nZachary\nHanna\nDillon\nNicholas\nMichael\nRobby\nGeoffrey\nKelly\nJoshua\nJordan\nDamian\nSamuel\nDavid\nDavid\nJessie\nNick\nJordan\nAdam\nSpencer\nJoseph\nMatthew\nDallas\nSamuel\nDavid\nLevi\nJacob\nAustin\nZachary\nMatthew\nMick\nGerrod\nZachary\nMichael\nLuke\nAlexander\nDoug\nAnthony\nAaron\nAndrew\nCharles\nMichael\nElita\nMax\nDaniel\nJames\nShawn\nShawn\nSergio\nTyrell\nMatthew\nAna\nAbdullah\nJack\nBrian\nBo\nEric\nChanning\nKevin\nHugh\nSerge\nMax\nKyle\nMatthew\nCameron\nKerby\nDerek\nPaul\nBrandon\nTaffie\nJacob\nJacaria\nChristina\nMichael\nKit\nUriah\nMinyuan\nAlexander\nKyle\nPatrick\nNathan\nJeromy\nElaine\nMatthew\nCody\nMarilyn\nKeenan\nBrady\nMatthew\nBrandon\nJose\nAndrew\nBenjamin\nWeston\nGregg\nBrian\nSam\nEric\nRobert\nDaniel\nJessi\nJoseph\nKellie\nJoshua\nJared\nKevin\nJason\nRobbie\nAdam\nChristian\nJoseph\nMichael\nZane\nAlex\nBrady\nPatricia\nMichael\nKyle\nJoseph\nJoseph\nJessi\nDaniel\nNathaniel\nDouglas\nDj\nJonathan\nTrevor\nLu\nSean\nMichael\nZach\nNatalie\nDerrick\nJacob\nEdward\nHarrison\nAndy\nJustin\nJared\nYujia\nGabriel\nLuke\nChanning\nGregory\nHannah\nAshleigh\nCarson\nZane\nOliver\nEliza\nDerek\nLevi\nAndrew\n";

TEST_CASE("Search"){
	Bnode* root = nullptr;
	std::string name;
	std::stringstream ss(file);
	//load from stream
	getline(ss >> std::ws, name);
	while(!ss.eof()){
		add(root, name);
		getline(ss >> std::ws, name);
	}
	SECTION("1"){
		REQUIRE(search(root, "Joe"     ) == 0);
	}
	SECTION("2"){
		REQUIRE(search(root, "Zach"    ) == 1);
	}
	SECTION("3"){
		REQUIRE(search(root, "Benjamin") == 2);
	}
	SECTION("4"){
		REQUIRE(search(root, "Kyle"    ) == 3);
	}
	SECTION("5"){
		REQUIRE(search(root, "Michael" ) == 7);
	}
}
TEST_CASE("Search Greater"){
	Bnode* root = nullptr;
	std::string name;
	std::stringstream ss(file);
	//load from stream
	getline(ss >> std::ws, name);
	while(!ss.eof()){
		add(root, name);
		getline(ss >> std::ws, name);
	}
	add(root, name);
	SECTION("1"){
		REQUIRE(search_greater(root, "Joe"     ) == 89);
	}
	SECTION("2"){
		REQUIRE(search_greater(root, "Zach"    ) == 5);
	}
	SECTION("3"){
		REQUIRE(search_greater(root, "Benjamin") == 154);
	}
	SECTION("4"){
		REQUIRE(search_greater(root, "Kyle"    ) == 66);
	}
	SECTION("5"){
		REQUIRE(search_greater(root, "Michael" ) == 41);
	}
}
TEST_CASE("Footer"){
	SECTION("Score") {
		std::cout << "\e[34m===============================================================================\e[0m\n";
		std::cout << "FOR ALL ERROR MESSAGES, THE FIRST VALUE IS THE ONE PROVIDED BY THE CLASS,\nAND THE SECOND VALUE IS THE DESIRED OUTPUT.\nSTART AT THE TOP AND WORK DOWNWARDS\n";
		std::cout << "\e[34m===============================================================================\e[0m\n";
	}
}