#include <iostream>
#include <string>

#include <cxxopts/cxxopts.hpp>

#include "game.hpp"
#include "othello.hpp"

using namespace main_savitch_14;

int main(int argc, const char* argv[])
{
	cxxopts::Options options("OthelloGame", "Othello the game");
	options.add_options()
  		("v,version", "Output a version of this program", cxxopts::value<bool>()->default_value("false"))
  		;
	auto result = options.parse(argc, argv);

	if (result["version"].as<bool>()) {
		std::cout << "v2022.1\n";
		return EXIT_SUCCESS;
	}

	Othello theGame;
	theGame.restart();
	theGame.play();

	return EXIT_SUCCESS;
}
