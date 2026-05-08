/***********************************************
 *
 *	Test cases for CS2401 Project 3, Planner
 *	Made by Kyle Chiasson, kc428921@ohio.edu
 *	Last updated 2/24/2024
 *	For automatic grading to work, do not change this file.
 *	Students are encouraged to read through to understand project requirements, however.
 *
 * ********************************************/
#define CATCH_CONFIG_MAIN
#include <iostream>
#include <fstream>
#include <sstream>
#include "catch.hpp"
#include "../planner.h"
#include "../date_time.h"
#include "../assignment.h"

const static std::string a1 =   "Web Assign 5\nCS3000\n2/23/2024\n5:00\n3/17/2024\n23:59\n";
const static std::string a2 = "Web Assign 6\nMATH2302\n2/23/2024\n5:00\n3/18/2024\n23:58\n";
const static std::string a3 =         "Resume\nET1500\n2/22/2024\n5:00\n3/18/2024\n23:59\n";
const static std::string a7 =       "Quiz 6\nMATH2302\n2/23/2024\n5:00\n3/19/2024\n23:58\n";
const static std::string a8 =      "LonCapa\nPHYS2054\n2/23/2024\n5:00\n3/19/2024\n23:59\n";
const static std::string a4 =   "Lab Report\nPHYS2054\n2/23/2024\n5:00\n3/20/2024\n23:58\n";
const static std::string a6 =         "Quiz 5\nCS2401\n2/24/2024\n5:00\n3/20/2024\n23:59\n";
const static std::string a0 =          "Lab 8\nCS2401\n2/23/2024\n5:00\n3/21/2024\n23:57\n";
const static std::string a5 =      "Project 3\nCS2401\n2/23/2024\n5:00\n3/21/2024\n23:58\n";
const static std::string a9 =     "Homework 2\nCS3000\n2/23/2024\n5:00\n3/21/2024\n23:59\n";
static std::streambuf* coutbuf = std::cout.rdbuf();

unsigned StrToTime(const std::string& str){
	std::stringstream ss(str);
	DateTime dt;
	dt.input(ss);
	return dt.minutes_since_1970();
}

TEST_CASE("Save/Load"){
	SECTION("Empty & Default Constructor"){
		std::stringstream iss(""), oss;
		Planner p;
		p.load(iss);
		p.save(oss);
		REQUIRE(oss.str() == iss.str());
	}
	SECTION("Normal"){
		std::stringstream iss(a1 + a2 + a3 + a7 + a8 + a4 + a6 + a0 + a5 + a9), oss;
		Planner p;
		p.load(iss);
		p.save(oss);
		REQUIRE(oss.str() == iss.str());
	}
}
TEST_CASE("Add"){
	SECTION("Empty"){
		std::stringstream lss(a1), oss;
		Assignment a;
		lss >> a;
		Planner p;
		p.add(a);
		p.save(oss);
		REQUIRE(oss.str() == a1);
	}
	SECTION("Front"){
		std::stringstream iss(a0), lss(a1), oss;
		Assignment a;
		lss >> a;
		Planner p;
		p.load(iss);
		p.add(a);
		p.save(oss);
		REQUIRE(oss.str() == a1 + a0);
	}
	SECTION("Back"){
		std::stringstream iss(a1), lss(a0), oss;
		Assignment a;
		lss >> a;
		Planner p;
		p.load(iss);
		p.add(a);
		p.save(oss);
		REQUIRE(oss.str() == a1 + a0);
	}
	SECTION("Middle"){
		std::stringstream iss(a1 + a9), lss(a0), oss;
		Assignment a;
		lss >> a;
		Planner p;
		p.load(iss);
		p.add(a);
		p.save(oss);
		REQUIRE(oss.str() == a1 + a0 + a9);
	}
}
TEST_CASE("Copy Consructor"){
	SECTION("Empty"){
		std::stringstream lss(a1), oss;
		Assignment a;
		lss >> a;
		Planner p1;
		Planner p2(p1);
		p1.add(a);
		p2.save(oss);
		REQUIRE(oss.str() == "");
	}
	SECTION("Normal"){
		std::stringstream iss(a2 + a3 + a7 + a8 + a4 + a6 + a0 + a5 + a9), lss(a1), oss;
		Assignment a;
		lss >> a;
		Planner p1;
		p1.load(iss);
		Planner p2(p1);
		p1.add(a);
		p2.save(oss);
		REQUIRE(oss.str() == iss.str());
	}
}
TEST_CASE("Assignement Operator"){
	SECTION("Empty"){
		std::stringstream lss(a1), oss;
		Assignment a;
		lss >> a;
		Planner p1, p2;
		p2 = p1;
		p1.add(a);
		p2.save(oss);
		REQUIRE(oss.str() == "");
	}
	SECTION("Normal"){
		std::stringstream iss(a2 + a3 + a7 + a8 + a4 + a6 + a0 + a5 + a9), lss(a1), oss;
		Assignment a;
		lss >> a;
		Planner p1, p2;
		p1.load(iss);
		p2 = p1;
		p1.add(a);
		p2.save(oss);
		REQUIRE(oss.str() == iss.str());
	}
	SECTION("Self"){
		std::stringstream iss(a2 + a3 + a7 + a8 + a4 + a6 + a0 + a5 + a9), oss;
		Planner p1;
		p1.load(iss);
		p1 = p1;
		p1.save(oss);
		REQUIRE(oss.str() == iss.str());
	}
}
//note: tests with no stylization
TEST_CASE("Display"){
	SECTION("Normal"){
		std::stringstream iss(a1 + a2 + a3 + a7 + a8 + a4 + a6 + a0 + a5 + a9), oss;
		Planner p;
		p.load(iss);
		p.display(oss);
		REQUIRE(oss.str() == iss.str());
	}
}
TEST_CASE("Find"){
	SECTION("First"){
		std::stringstream iss(a1 + a2 + a3 + a7 + a8 + a4 + a6 + a0 + a5 + a9), oss;
		Planner p;
		p.load(iss);
		p.find("Web Assign 5").output(oss);
		REQUIRE(oss.str() == a1);
	}
	SECTION("Last"){
		std::stringstream iss(a1 + a2 + a3 + a7 + a8 + a4 + a6 + a0 + a5 + a9), oss;
		Planner p;
		p.load(iss);
		p.find("Homework 2").output(oss);
		REQUIRE(oss.str() == a9);
	}
	SECTION("Middle"){
		std::stringstream iss(a1 + a2 + a3 + a7 + a8 + a4 + a6 + a0 + a5 + a9), oss;
		Planner p;
		p.load(iss);
		p.find("Quiz 6").output(oss);
		REQUIRE(oss.str() == a7);
	}
	SECTION("Not In List"){
		std::stringstream iss(a1 + a2 + a3 + a7 + a8 + a4 + a6 + a0 + a5 + a9), oss;
		Planner p;
		p.load(iss);
		REQUIRE(p.find("Quiz 12") == Assignment());
	}
}
TEST_CASE("Remove"){
	SECTION("First"){
		std::stringstream iss(a1 + a2 + a3 + a7 + a8 + a4 + a6 + a0 + a5 + a9), oss;
		Planner p;
		p.load(iss);
		p.remove("Web Assign 5");
		p.save(oss);
		REQUIRE(oss.str() == a2 + a3 + a7 + a8 + a4 + a6 + a0 + a5 + a9);
	}
	SECTION("Last"){
		std::stringstream iss(a1 + a2 + a3 + a7 + a8 + a4 + a6 + a0 + a5 + a9), oss;
		Planner p;
		p.load(iss);
		p.remove("Homework 2");
		p.save(oss);
		REQUIRE(oss.str() == a1 + a2 + a3 + a7 + a8 + a4 + a6 + a0 + a5);
	}
	SECTION("Middle"){
		std::stringstream iss(a1 + a2 + a3 + a7 + a8 + a4 + a6 + a0 + a5 + a9), oss;
		Planner p;
		p.load(iss);
		p.remove("Quiz 6");
		p.save(oss);
		REQUIRE(oss.str() == a1 + a2 + a3 + a8 + a4 + a6 + a0 + a5 + a9);
	}
	SECTION("Not In List"){
		std::stringstream iss(a1 + a2 + a3 + a7 + a8 + a4 + a6 + a0 + a5 + a9), oss;
		Planner p;
		p.load(iss);
		p.remove("Quiz 12");
		p.save(oss);
		REQUIRE(oss.str() == iss.str());
	}
	SECTION("To Empty"){
		std::stringstream iss(a1), oss;
		Planner p;
		p.load(iss);
		p.remove("Web Assign 5");
		p.save(oss);
		REQUIRE(oss.str() == "");
	}
}
TEST_CASE("Waiting"){
	SECTION("Normal"){
		std::stringstream iss(a1 + a2 + a3 + a7 + a8 + a4 + a6 + a0 + a5 + a9);
		Planner p;
		p.load(iss);
		REQUIRE(p.waiting() == 10);
	}
}
TEST_CASE("Due Next"){
	SECTION("Empty"){
		Planner p;
		REQUIRE(p.due_next() == 0);
	}
	SECTION("Normal"){
		std::stringstream iss(a1 + a2 + a3 + a7 + a8 + a4 + a6 + a0 + a5 + a9);
		Planner p;
		p.load(iss);
		DateTime now;
		now.make_now();
		REQUIRE(p.due_next() == StrToTime("3/17/2024\n23:59\n") - now.minutes_since_1970());
	}
}
TEST_CASE("Average Wait"){
	SECTION("Empty"){
		Planner p;
		REQUIRE(p.average_wait() == 0);
	}
	SECTION("Normal"){
		std::stringstream iss(a1 + a2 + a3 + a7 + a8 + a4 + a6 + a0 + a5 + a9);
		Planner p;
		p.load(iss);
		DateTime now;
		now.make_now();
		REQUIRE(p.average_wait() == (double)(now.minutes_since_1970() -StrToTime("2/23/2024\n5:00\n")));
	}
}
TEST_CASE("Oldest"){
	SECTION("Empty"){
		Planner p;
		REQUIRE(p.oldest() == 0);
	}
	SECTION("Normal"){
		std::stringstream iss(a1 + a2 + a3 + a7 + a8 + a4 + a6 + a0 + a5 + a9);
		Planner p;
		p.load(iss);
		DateTime now;
		now.make_now();
		REQUIRE(p.oldest() == now.minutes_since_1970() - StrToTime("2/22/2024\n5:00\n"));
	}
}
TEST_CASE("Newest"){
	SECTION("Empty"){
		Planner p;
		REQUIRE(p.newest() == 0);
	}
	SECTION("Normal"){
		std::stringstream iss(a1 + a2 + a3 + a7 + a8 + a4 + a6 + a0 + a5 + a9);
		Planner p;
		p.load(iss);
		DateTime now;
		now.make_now();
		REQUIRE(p.newest() == now.minutes_since_1970() - StrToTime("2/24/2024\n5:00\n"));
	}
}
TEST_CASE("Find All"){
	SECTION("Normal"){
		std::stringstream iss(a1 + a2 + a3 + a7 + a8 + a4 + a6 + a0 + a5 + a9), lss("3/20/2024\n00:00"), oss;
		Planner p;
		DateTime dt;
		dt.input(lss);
		p.load(iss);
		std::cout.rdbuf(oss.rdbuf());
		p.find_all(dt);
		std::cout.rdbuf(coutbuf);
		REQUIRE(oss.str() == "Assignment Name: Web Assign 5\n         Course: CS3000\n   Date entered: 2/23/2024 at 5:00\n       Due Date: 3/17/2024 at 23:59\n\nAssignment Name: Web Assign 6\n         Course: MATH2302\n   Date entered: 2/23/2024 at 5:00\n       Due Date: 3/18/2024 at 23:58\n\nAssignment Name: Resume\n         Course: ET1500\n   Date entered: 2/22/2024 at 5:00\n       Due Date: 3/18/2024 at 23:59\n\nAssignment Name: Quiz 6\n         Course: MATH2302\n   Date entered: 2/23/2024 at 5:00\n       Due Date: 3/19/2024 at 23:58\n\nAssignment Name: LonCapa\n         Course: PHYS2054\n   Date entered: 2/23/2024 at 5:00\n       Due Date: 3/19/2024 at 23:59\n\n");
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
