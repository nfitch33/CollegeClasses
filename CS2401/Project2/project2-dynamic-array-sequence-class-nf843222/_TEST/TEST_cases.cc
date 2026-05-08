/***********************************************
 *
 *	Test cases for CS2401 Project 2, Dynamic Sequence Classes
 *	Made by Kyle Chiasson, kc428921@ohio.edu
 *	Last updated 2/12/2024
 *	For automatic grading to work, do not change this file.
 *	Students are encouraged to read through to understand project requirements, however.
 *
 * ********************************************/
#define CATCH_CONFIG_MAIN
#include <iostream>
#include <fstream>
#include <sstream>
#include "catch.hpp"
#include "../profile.h"
#include "../instafollows.h"

static const std::string P0 = "Kyle C\n4/4/2004\n";
static const std::string P1 = "Will K\n12/5/2004\n";
static const std::string P2 = "Luke W\n4/17/2004\n";
static const std::string P3 = "Matthew B\n3/27/2004\n";
static const std::string P4 = "Noah L\n5/3/2002\n";
static const std::string P5 = "Zach L\n5/13/2004\n";
static const std::string P6 = "Michael T\n5/17/2002\n";
static const std::string P7 = "Drew M\n6/19/2003\n";
static const std::string P8 = "Ben C\n11/10/2003\n";
static const std::string P9 = "Mary A\n7/16/2004\n";
static const std::string PDefault = "N/A\n1/1/1\n";

//Profile Tests
TEST_CASE("Profile: Basic Functions"){
	SECTION("Constructor & Getters") {
		Profile p1;
		REQUIRE(p1.get_name() == "N/A");
		REQUIRE(p1.get_bday() == Date());
	}
}
TEST_CASE("Profile: Comparisons"){
	Profile p1;
	Profile p2("N/A", Date());
	Profile p3("Bob Smith", Date(17, 5, 2004));
	SECTION("Equals") {
		REQUIRE(p1 == p2);
	}
	SECTION("Not Equals") {
		REQUIRE(p1 != p3);
	}
}
TEST_CASE("Profile: I/O"){
	SECTION("Input") {
		std::stringstream s;
		s.str("Bob Smith\n5/17/2004\n");
		Profile p;
		p.input(s);
		REQUIRE(p.get_name() == "Bob Smith");
		REQUIRE(p.get_bday() == Date(17, 5, 2004));
	}
	SECTION("Output") {
		std::stringstream s;
		Profile p("Bob Smith", Date(17, 5, 2004));
		p.output(s);
		REQUIRE(s.str() == "Bob Smith\n5/17/2004\n");
	}
}
//Instafollows Tests
//Note: Tests assume constructor and resize work
TEST_CASE("Instafollows: I/O"){
	SECTION("Normal"){
		std::stringstream s;
		s.str(P0 + P1 + P2 + P3 + P4 + P5 + P6 + P7 + P8 + P9);
		InstaFollows iF;
		iF.load(s);
		std::stringstream o;
		iF.save(o);
		REQUIRE(o.str() == s.str());
	}
}
//Note: this case requires start and advance to work properly
TEST_CASE("Instafollows: Sequence"){
	SECTION("is_item inside"){
		std::stringstream s;
		InstaFollows iF;
		s.str(P0 + P1 + P2 + P3 + P4 + P5 + P6 + P7 + P8 + P9);
		iF.load(s);
		iF.start();
		REQUIRE(iF.is_item() == true);
	}
	SECTION("is_item outside"){
		std::stringstream s;
		InstaFollows iF;
		s.str(P0 + P1 + P2 + P3 + P4 + P5 + P6 + P7 + P8 + P9);
		iF.load(s);
		iF.start();
		for(int i = 0; i < 10; i++)
			iF.advance();
		REQUIRE(iF.is_item() == false);
	}
	SECTION("current inside"){
		std::stringstream s, o;
		InstaFollows iF;
		s.str(P0 + P1 + P2 + P3 + P4 + P5 + P6 + P7 + P8 + P9);
		iF.load(s);
		iF.start();
		o << iF.current();
		REQUIRE(o.str() == P0);
	}
	SECTION("current outside"){
		std::stringstream s, o;
		InstaFollows iF;
		s.str(P0 + P1 + P2 + P3 + P4 + P5 + P6 + P7 + P8 + P9);
		iF.load(s);
		iF.start();
		for(int i = 0; i < 10; i++)
			iF.advance();
		o << iF.current();
		REQUIRE(o.str() == PDefault);
	}
	SECTION("remove_current inside"){
		std::stringstream s, o1, o2;
		InstaFollows iF;
		s.str(P0 + P1 + P2 + P3 + P4 + P5 + P6 + P7 + P8 + P9);
		iF.load(s);
		iF.start();
		iF.advance();
		iF.remove_current();
		iF.save(o1);
		o2 << iF.current();
		REQUIRE(o1.str() == P0 + P2 + P3 + P4 + P5 + P6 + P7 + P8 + P9);
		REQUIRE(o2.str() == P2);
	}
	SECTION("remove_current outside"){
		std::stringstream s, o1, o2;
		InstaFollows iF;
		s.str(P0 + P1 + P2 + P3 + P4 + P5 + P6 + P7 + P8 + P9);
		iF.load(s);
		iF.start();
		for(int i = 0; i < 10; i++)
			iF.advance();
		iF.remove_current();
		iF.save(o1);
		o2 << iF.current();
		REQUIRE(o1.str() == s.str());
		REQUIRE(o2.str() == PDefault);
	}
	Profile profile;
	std::stringstream profileSS;
	profileSS.str(P9);
	profileSS >> profile;
	SECTION("insert inside"){
		std::stringstream s, o1, o2;
		InstaFollows iF;
		s.str(P0 + P1 + P2 + P3 + P4 + P5 + P6 + P7 + P8);
		iF.load(s);
		iF.start();
		iF.advance();
		iF.insert(profile);
		iF.save(o1);
		o2 << iF.current();
		REQUIRE(o1.str() == P0 + P9 + P1 + P2 + P3 + P4 + P5 + P6 + P7 + P8);
		REQUIRE(o2.str() == P1);
	}
	SECTION("insert outside"){
		std::stringstream s;
		std::stringstream o1;
		std::stringstream o2;
		InstaFollows iF;
		s.str(P0 + P1 + P2 + P3 + P4 + P5 + P6 + P7 + P8);
		iF.load(s);
		iF.start();
		for(int i = 0; i < 10; i++)
			iF.advance();
		iF.insert(profile);
		iF.save(o1);
		o2 << iF.current();

		REQUIRE(o1.str() == P9 + P0 + P1 + P2 + P3 + P4 + P5 + P6 + P7 + P8);
		REQUIRE(o2.str() == PDefault);
	}
	SECTION("attach inside"){
		std::stringstream s;
		std::stringstream o1;
		std::stringstream o2;
		InstaFollows iF;
		s.str(P0 + P1 + P2 + P3 + P4 + P5 + P6 + P7 + P8);
		iF.load(s);
		iF.start();
		iF.advance();
		iF.attach(profile);
		iF.save(o1);
		o2 << iF.current();
		REQUIRE(o1.str() == P0 + P1 + P9 + P2 + P3 + P4 + P5 + P6 + P7 + P8);
		REQUIRE(o2.str() == P1);
	}
	SECTION("attach outside"){
		std::stringstream s;
		std::stringstream o1;
		std::stringstream o2;
		InstaFollows iF;
		s.str(P0 + P1 + P2 + P3 + P4 + P5 + P6 + P7 + P8);
		iF.load(s);
		iF.start();
		for(int i = 0; i < 10; i++)
			iF.advance();
		iF.attach(profile);
		iF.save(o1);
		o2 << iF.current();
		REQUIRE(o1.str() == P0 + P1 + P2 + P3 + P4 + P5 + P6 + P7 + P8 + P9);
		REQUIRE(o2.str() == PDefault);
	}
}
TEST_CASE("Instafollows: Big3"){
	SECTION("Copy Constructor"){
		std::stringstream s, o;
		InstaFollows iF1;
		s.str(P0 + P1 + P2 + P3 + P4 + P5 + P6 + P7 + P8 + P9);
		iF1.load(s);
		InstaFollows iF2(iF1);
		iF1.start();
		iF1.remove_current();
		iF2.save(o);
		REQUIRE(o.str() == s.str());
	}
	SECTION("Assignment operator"){
		std::stringstream s, o;
		InstaFollows iF1, iF2;
		s.str(P0 + P1 + P2 + P3 + P4 + P5 + P6 + P7 + P8 + P9);
		iF1.load(s);
		iF2 = iF1;
		iF1.start();
		iF1.remove_current();
		iF2.save(o);
		REQUIRE(o.str() == s.str());
	}
	SECTION("Assignment operator: self assignment"){
		std::stringstream s, o;
		InstaFollows iF1;
		s.str(P0 + P1 + P2 + P3 + P4 + P5 + P6 + P7 + P8 + P9);
		iF1.load(s);
		iF1 = iF1;
		iF1.save(o);
		REQUIRE(o.str() == s.str());
	}
}
//This test is unstylized and does not matter if it passes completely
TEST_CASE("Instafollows: show_all"){
	SECTION("normal"){
		std::stringstream s, o;
		InstaFollows iF;
		s.str(P0 + P1 + P2 + P3 + P4 + P5 + P6 + P7 + P8 + P9);
		iF.load(s);
		iF.show_all(o);
		REQUIRE(o.str() == s.str());
	}
}
//
TEST_CASE("Instafollows: sorting"){
	SECTION("bday_sort"){
		std::stringstream s, o;
		InstaFollows iF;
		s.str(P0 + P1 + P2 + P3 + P4 + P5 + P6 + P7 + P8 + P9);
		iF.load(s);
		iF.bday_sort();
		iF.save(o);
		REQUIRE(o.str() == P4 + P6 + P7 + P8 + P3 + P0 + P2 + P5 + P9 + P1);
	}
}
TEST_CASE("Instafollows: find_profile"){
	SECTION("in list"){
		std::stringstream s, o;
		InstaFollows iF;
		s.str(P0 + P1 + P2 + P3 + P4 + P5 + P6 + P7 + P8 + P9);
		iF.load(s);
		o << iF.find_profile("Kyle C");
		REQUIRE(o.str() == P0);
	}
	SECTION("not in list"){
		std::stringstream s, o;
		InstaFollows iF;
		s.str(P0 + P1 + P2 + P3 + P4 + P5 + P6 + P7 + P8 + P9);
		iF.load(s);
		o << iF.find_profile("Ian Y");
		REQUIRE(o.str() == PDefault);
	}
}
TEST_CASE("Footer"){
	SECTION("Score") {
		std::cout << "\e[34m===============================================================================\e[0m\n";
		std::cout << "FOR ALL ERROR MESSAGES, THE FIRST VALUE IS THE ONE PROVIDED BY THE CLASS,\nAND THE SECOND VALUE IS THE DESIRED OUTPUT.\nSTART AT THE TOP AND WORK DOWNWARDS\n";
		std::cout << "NOTE: Some of these tests are subjective based on your output format,\n but all should look similar.\n";
		std::cout << "\e[34m===============================================================================\e[0m\n";
	}
}
