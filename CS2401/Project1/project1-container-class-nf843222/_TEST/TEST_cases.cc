/***********************************************
 *
 *	Test cases for CS2401 Project 1, Plant Nursery
 *	Made by Kyle Chiasson, kc428921@ohio.edu
 *	Last updated 1/25/2024
 *	For automatic grading to work, do not change this file.
 *	Students are encouraged to read through to understand project requirements, however.
 *
 * ********************************************/
#define CATCH_CONFIG_MAIN
#include <iostream>
#include <fstream>
#include <sstream>
#include "catch.hpp"
#include "../plant.h"
#include "../plantNursery.h"
#include "../date.h"

//static int score = 0;
static const std::string plant0 = "flower\nblue\n12/1/2023\n5\n";
static const std::string plant1 = "flower\npurple\n7/5/2023\n1\n";
static const std::string plant2 = "fern\nblue\n1/20/2024\n3\n";
static const std::string plant3 = "flower\norange\n7/30/2023\n2\n";
static const std::string plant4 = "flower\nred\n1/25/2024\n7\n";
static const std::string plant5 = "zebra grass\nyellow\n11/17/2023\n3\n";
static const std::string plant6 = "flower\nyellow\n5/9/2023\n1\n";
static const std::string plant7 = "zebra grass\nblue\n10/1/2024\n5\n";
static const std::string plant8 = "fern\nred\n7/8/2023\n4\n";
static const std::string plant9 = "fern\ngreen\n6/14/2023\n6\n";
static std::streambuf *coutbuf = std::cout.rdbuf();

TEST_CASE("Plant: Extraction") {
	SECTION("Normal Input") {
		std::stringstream s;
		Plant p;
		s.str(plant0);
		s >> p;
		REQUIRE(p.get_name() == "flower");
		REQUIRE(p.get_color() == "blue");
		REQUIRE(p.get_cameIn() == Date(1, 12, 2023));
		REQUIRE(p.get_stock() == 5);
	}
	SECTION("Input With spaces") {
		std::stringstream s;
		Plant p;
		s.str(plant5);
		s >> p;
		REQUIRE(p.get_name() == "zebra grass");
		REQUIRE(p.get_color() == "yellow");
		REQUIRE(p.get_cameIn() == Date(17, 11, 2023));
		REQUIRE(p.get_stock() == 3);
	}
}
TEST_CASE("Plant: Insertion"){
	SECTION("Normal Output") {
		std::stringstream s;
		Plant p("flower", "blue", Date(1, 12, 2023), 5);
		s << p;
		REQUIRE(s.str() == plant0);
	}
}
TEST_CASE("Plant Nursery: load_from_file && save"){
	SECTION("Normal"){
		PlantNursery pn;
		std::stringstream s;
		std::stringstream o;
		s.str(plant0 + plant1 + plant2 + plant3 + plant4 + plant5 + plant6 + plant7 + plant8 + plant9);
		pn.load_from_file(s);
		pn.save(o);
		REQUIRE(o.str() == s.str());
	}
}
TEST_CASE("Plant Nursery: show_all"){
	SECTION("Normal Output"){
		PlantNursery pn;
		std::stringstream s;
		std::stringstream o;
		s.str(plant0 + plant1 + plant2 + plant3 + plant4 + plant5 + plant6 + plant7 + plant8 + plant9);
		pn.load_from_file(s);
		pn.show_all(o);
		REQUIRE(o.str() == s.str());
	}
}
TEST_CASE("Plant Nursery: add_plant"){
	SECTION("Single"){
		std::stringstream s;
		std::stringstream o;
		PlantNursery pn;
		s.str(plant0);
		pn.add_plant(s);
		pn.save(o);
		REQUIRE(o.str() == s.str());
	}
	SECTION("Multiple"){
		std::stringstream s;
		std::stringstream o;
		PlantNursery pn;
		s.str(plant0 + plant1 + plant2 + plant3 + plant4 + plant5 + plant6 + plant7 + plant8 + plant9);
		for(int i = 0; i < 10; i++)
			pn.add_plant(s);
		pn.save(o);
		REQUIRE(o.str() == s.str());
	}
	SECTION("Too Many"){
		std::stringstream s;
		std::stringstream s2;
		std::stringstream o;
		PlantNursery pn;
		for(int i = 0; i < 200; i++)
			s.str() += plant0;
		s2.str() += plant0;
		pn.load_from_file(s2);
		pn.save(o);
		REQUIRE(o.str() == s.str());
	}
}
TEST_CASE("Plant Nursery: remove"){
	SECTION("Single"){
		PlantNursery pn;
		std::stringstream s;
		std::stringstream o;
		s.str(plant0 + plant1 + plant2 + plant3 + plant4 + plant5 + plant6 + plant7 + plant8 + plant9);
		pn.load_from_file(s);
		pn.remove("flower", "orange");
		pn.save(o);
		REQUIRE(o.str() == plant0 + plant1 + plant2 + plant9 + plant4 + plant5 + plant6 + plant7 + plant8);
	}
	SECTION("Multiple"){
		PlantNursery pn;
		std::stringstream s;
		std::stringstream o;
		s.str(plant0 + plant1 + plant2 + plant3 + plant4 + plant5 + plant6 + plant7 + plant8 + plant9);
		pn.load_from_file(s);
		pn.remove("flower", "orange");
		pn.remove("zebra grass", "blue");
		pn.save(o);
		REQUIRE(o.str() == plant0 + plant1 + plant2 + plant9 + plant4 + plant5 + plant6 + plant8);
	}
	SECTION("Not In List"){
		PlantNursery pn;
		std::stringstream s;
		std::stringstream o;
		s.str(plant0 + plant1 + plant2 + plant3 + plant4 + plant5 + plant6 + plant7 + plant8 + plant9);
		pn.load_from_file(s);
		pn.remove("pineapple", "yellow");
		pn.save(o);
		REQUIRE(o.str() == s.str());
	}
}
TEST_CASE("Plant Nursery: change_stock_amt"){
	SECTION("Add"){
		PlantNursery pn;
		std::stringstream s;
		std::stringstream o;
		s.str(plant0 + plant1 + plant2 + plant3 + plant4 + plant5 + plant6 + plant7 + plant8 + plant9);
		pn.load_from_file(s);
		pn.change_stock_amt("flower", "orange", 1);
		pn.save(o);
		REQUIRE(o.str() == plant0 + plant1 + plant2 + "flower\norange\n7/30/2023\n3\n" + plant4 + plant5 + plant6 + plant7 + plant8 + plant9);
	}
	SECTION("Subtract"){
		PlantNursery pn;
		std::stringstream s;
		std::stringstream o;
		s.str(plant0 + plant1 + plant2 + plant3 + plant4 + plant5 + plant6 + plant7 + plant8 + plant9);
		pn.load_from_file(s);
		pn.change_stock_amt("zebra grass", "blue", -1);
		pn.save(o);
		REQUIRE(o.str() == plant0 + plant1 + plant2 + plant3 + plant4 + plant5 + plant6 + "zebra grass\nblue\n10/1/2024\n4\n" + plant8 + plant9);
	}
	SECTION("Not In List"){
		PlantNursery pn;
		std::stringstream s;
		std::stringstream o;
		s.str(plant0 + plant1 + plant2 + plant3 + plant4 + plant5 + plant6 + plant7 + plant8 + plant9);
		pn.load_from_file(s);
		pn.change_stock_amt("pineapple", "yellow", 1);
		pn.save(o);
		REQUIRE(o.str() == s.str());
	}
}
TEST_CASE("Plant Nursery: sorts"){
	SECTION("name_sort"){
		PlantNursery pn;
		std::stringstream s;
		std::stringstream o;
		s.str(plant0 + plant1 + plant2 + plant3 + plant4 + plant5 + plant6 + plant7 + plant8 + plant9);
		pn.load_from_file(s);
		pn.name_sort();
		pn.save(o);
		REQUIRE(o.str() == plant2 + plant8 + plant9  + plant0 + plant1 + plant3 + plant4 + plant6 + plant5 + plant7);
	}
	SECTION("date_sort"){
		PlantNursery pn;
		std::stringstream s;
		std::stringstream o;
		s.str(plant0 + plant1 + plant2 + plant3 + plant4 + plant5 + plant6 + plant7 + plant8 + plant9);
		pn.load_from_file(s);
		pn.date_sort();
		pn.save(o);
		REQUIRE(o.str() == plant6 + plant9 + plant1 + plant8 + plant3 + plant5 + plant0 + plant2 + plant4 + plant7);
	}
	SECTION("stock_sort"){
		PlantNursery pn;
		std::stringstream s;
		std::stringstream o;
		s.str(plant0 + plant1 + plant2 + plant3 + plant4 + plant5 + plant6 + plant7 + plant8 + plant9);
		pn.load_from_file(s);
		pn.stock_sort();
		pn.save(o);
		REQUIRE(o.str() == plant1 + plant6 + plant3 + plant2 + plant5 + plant8 + plant0 + plant7 + plant9 + plant4);
	}
}
TEST_CASE("Plant Nursery: show_plants"){
	SECTION("Normal"){
		PlantNursery pn;
		std::stringstream s;
		std::stringstream o;
		s.str(plant0 + plant1 + plant2 + plant3 + plant4 + plant5 + plant6 + plant7 + plant8 + plant9);
		pn.load_from_file(s);
		std::cout.rdbuf(o.rdbuf());
		pn.show_plants("red");
		REQUIRE(o.str() == "Name: flower\nColor: red\nCame In: 1/25/2024\nStock: 7\nName: fern\nColor: red\nCame In: 7/8/2023\nStock: 4\n");
	}
	SECTION("Not In List"){
		PlantNursery pn;
		std::stringstream s;
		std::stringstream o;
		s.str(plant0 + plant1 + plant2 + plant3 + plant4 + plant5 + plant6 + plant7 + plant8 + plant9);
		pn.load_from_file(s);
		std::cout.rdbuf(o.rdbuf());
		pn.show_plants("white");
		REQUIRE(o.str() == "");
	}
}
TEST_CASE("Plant Nursery: show_before"){
	SECTION("Normal"){
		PlantNursery pn;
		std::stringstream s;
		std::stringstream o;
		s.str(plant0 + plant1 + plant2 + plant3 + plant4 + plant5 + plant6 + plant7 + plant8 + plant9);
		pn.load_from_file(s);
		std::cout.rdbuf(o.rdbuf());
		pn.show_before(Date(1, 7, 2023));
		REQUIRE(o.str() == "Name: flower\nColor: yellow\nCame In: 5/9/2023\nStock: 1\nName: fern\nColor: green\nCame In: 6/14/2023\nStock: 6\n");
	}
	SECTION("Prior to list"){
		PlantNursery pn;
		std::stringstream s;
		std::stringstream o;
		s.str(plant0 + plant1 + plant2 + plant3 + plant4 + plant5 + plant6 + plant7 + plant8 + plant9);
		pn.load_from_file(s);
		std::cout.rdbuf(o.rdbuf());
		pn.show_before(Date(1, 1, 2023));
		REQUIRE(o.str() == "");
	}
}
TEST_CASE("Plant Nursery: show_colors"){
	SECTION("Normal"){
		PlantNursery pn;
		std::stringstream s;
		std::stringstream o;
		s.str(plant0 + plant1 + plant2 + plant3 + plant4 + plant5 + plant6 + plant7 + plant8 + plant9);
		pn.load_from_file(s);
		std::cout.rdbuf(o.rdbuf());
		pn.show_colors("zebra grass");
		REQUIRE(o.str() == "Name: zebra grass\nColor: yellow\nCame In: 11/17/2023\nStock: 3\nName: zebra grass\nColor: blue\nCame In: 10/1/2024\nStock: 5\n");
	}
	SECTION("Not In List"){
		PlantNursery pn;
		std::stringstream s;
		std::stringstream o;
		s.str(plant0 + plant1 + plant2 + plant3 + plant4 + plant5 + plant6 + plant7 + plant8 + plant9);
		pn.load_from_file(s);
		std::cout.rdbuf(o.rdbuf());
		pn.show_colors("pineapple");
		REQUIRE(o.str() == "");
	}
}
TEST_CASE("Plant Nursery: average"){
	SECTION("Normal"){
		PlantNursery pn;
		std::stringstream s;
		s.str(plant0 + plant1 + plant2 + plant3 + plant4 + plant5 + plant6 + plant7 + plant8 + plant9);
		pn.load_from_file(s);
		REQUIRE(pn.average() == (1.0f * 37 / 10));
	}
}
TEST_CASE("Footer"){
	SECTION("Score") {
		std::cout.rdbuf(coutbuf);
		std::cout << "\e[34m===============================================================================\e[0m\n";
		std::cout << "FOR ALL ERROR MESSAGES, THE FIRST VALUE IS THE ONE PROVIDED BY THE CLASS,\nAND THE SECOND VALUE IS THE DESIRED OUTPUT.\nSTART AT THE TOP AND WORK DOWNWARDS\n";
		std::cout << "NOTE: Some of these tests are subjective based on your output format,\n but all should look similar.\n";
		std::cout << "\e[34m===============================================================================\e[0m\n";
	}
}
