/** @file
 * @author Rufus Bobcat
 * @date: 3/24/2025
 * @brief Course: cs3560, Part of the given source code for a project in cs2401
 * see also: @ref game.hpp
 */
#pragma once

enum color {black, white, blank};

class piece {
public:
	piece() {theColor = blank;}

	void flip()
	{
		if (theColor == white) {
			theColor = black;
		}
		else if (theColor == black) {
			theColor = white;
		}
	}

	bool is_blank()const {return theColor == blank;}
	bool is_black()const {return theColor == black;}
	bool is_white()const {return theColor == white;}
	void set_white() {theColor = white;}
	void set_black() {theColor = black;}

private:
	color theColor;

};
