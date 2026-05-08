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
#include "../numlist.h"
#include "catch.hpp"

static const std::string smaller = "14140\n22089\n26522\n5203\n9172\n4435\n28318\n24583\n6816\n4587\n";
static const std::string larger = "16839\n5759\n10114\n17516\n31052\n5628\n23011\n7420\n16213\n4087\n2750\n12768\n9085\n12061\n32226\n17544\n25090\n21184\n25138\n25567\n26967\n4979\n20496\n10312\n11368\n30055\n17032\n13146\n19883\n25737\n30525\n28506\n28395\n22103\n24852\n19068\n12755\n11654\n6562\n27097\n13629\n15189\n32086\n4144\n6968\n31407\n24166\n13404\n25563\n24835\n31354\n921\n10445\n24804\n7963\n19319\n1423\n31328\n10458\n1946\n14480\n29984\n18752\n3895\n18671\n8260\n16249\n7758\n15630\n13307\n28607\n13991\n11739\n12517\n1415\n5263\n17117\n22826\n3182\n13135\n25344\n8023\n11234\n7537\n9761\n9980\n29072\n1202\n21337\n13062\n22161\n24006\n30730\n7645\n27476\n31694\n25515\n";
static std::streambuf *coutbuf = std::cout.rdbuf();

bool sorted(const NumList& list){
	for(size_t i = 0; i < list.size() - 1; i++)
		if(list.get_item(i) > list.get_item(i + 1))
			return false;
	return true;
}

TEST_CASE("Numlist: load_from_file"){
	SECTION("smaller.dat"){
		std::stringstream s;
		std::stringstream o;
		NumList nl;
		s.str(smaller);
		nl.load_from_file(s);
		std::cout.rdbuf(o.rdbuf());
		nl.see_all();
		REQUIRE(o.str() == s.str());
	}
	SECTION("larger.dat"){
		std::stringstream s;
		std::stringstream o;
		NumList nl;
		s.str(larger);
		nl.load_from_file(s);
		std::cout.rdbuf(o.rdbuf());
		nl.see_all();
		REQUIRE(o.str() == s.str());
	}
}
TEST_CASE("Numlist: save_to_file"){
	SECTION("smaller.dat"){
		std::stringstream s;
		std::stringstream o;
		NumList nl;
		s.str(smaller);
		nl.load_from_file(s);
		nl.save_to_file(o);
		REQUIRE(o.str() == s.str());
	}
	SECTION("larger.dat"){
		std::stringstream s;
		std::stringstream o;
		NumList nl;
		s.str(larger);
		nl.load_from_file(s);
		nl.save_to_file(o);
		REQUIRE(o.str() == s.str());
	}
}
TEST_CASE("Numlist: i_sort"){
	SECTION("smaller.dat"){
		std::stringstream s;
		std::stringstream o;
		NumList nl;
		s.str(smaller);
		nl.load_from_file(s);
		nl.i_sort();
		REQUIRE(sorted(nl));
	}
	SECTION("larger.dat"){
		std::stringstream s;
		std::stringstream o;
		NumList nl;
		s.str(larger);
		nl.load_from_file(s);
		nl.i_sort();
		REQUIRE(sorted(nl));
	}
}
TEST_CASE("Footer"){
	SECTION("Score") {
		std::cout.rdbuf(coutbuf);
		std::cout << "\e[34m===============================================================================\e[0m\n";
		std::cout << "FOR ALL ERROR MESSAGES, THE FIRST VALUE IS THE ONE PROVIDED BY THE CLASS,\nAND THE SECOND VALUE IS THE DESIRED OUTPUT.\nSTART AT THE TOP AND WORK DOWNWARDS\n";
		std::cout << "\e[34m===============================================================================\e[0m\n";
	}
}