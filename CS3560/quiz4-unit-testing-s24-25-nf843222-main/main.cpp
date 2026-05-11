/**
 * @file main.cpp
 * @author Taylor Bruening
 * @brief main for othello game
 */
#include "othello.hpp"
#include <cstdlib>
#include <iostream>
#include <string>

#include <cxxopts.hpp>

using namespace std;

int main(int argc, const char* argv[]) {
  // clang-format off
  cxxopts::Options options("OthelloGame", "CLI Game of Othello");
	options.add_options()
  		("v,version", "Output a version of this program", cxxopts::value<bool>()->default_value("false"))
  		;
  // clang-format on
	auto result = options.parse(argc, argv);

	if (result["version"].as<bool>()) {
		std::cout << "v2022.1" << std::endl;
		return EXIT_SUCCESS;
	}

  Othello myg;

  cout << BOLD << "\nOTHELLO\n" << RESET;
  cout << "Enter lower case " << RED << "xx" << RESET << " to skip a turn\n\n";
  myg.play();
  myg.victory();

  return 0;
}
