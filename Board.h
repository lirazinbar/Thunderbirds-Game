#pragma once
#include <iostream>

class Board {
public:
	constexpr static int Width = 82; // 80 chars + '\n' + '\0'
	constexpr static int Height = 25;
private:
	char board[Height][Width] = {
		"_____________________________________________________________________________\n",
	   "|      Active Ship:            Time Left:               Lives:                |\n",
	   "|_____________________________________________________________________________|\n",
	   "|                                                                             |\n",
	   "|                                                                             |\n",
	   "|                                                                             |\n",
	   "|                                                                             |\n",
	   "|                                         #                                   |\n",
	   "|                                                                             |\n",
	   "|                                                                             |\n",
	   "|                                                                             |\n",
	   "|                                                                             |\n",
	   "|                                                                             |\n",
	   "|                                                                             |\n",
	   "|                                   @                                         |\n",
	   "|                                                                             |\n",
	   "|                                                                             |\n",
	   "|                                                                             |\n",
	   "|                                                                             |\n",
	   "|                                                                             |\n",
	   "|                                                                             |\n",
	   "|                                                                             |\n",
	   "                                                                              |\n",
	   "                                                                              |\n",
	   "|_____________________________________________________________________________|\n",
	};
public:
	char get(int x, int y) const {
		return board[y][x];
	}
	void set(int x, int y, char c) {
		board[y][x] = c;
	}
	void print() const {
		for (size_t row = 0; row < Height; ++row) {
			std::cout << board[row];
		}
	}
};