#pragma once
#include <iostream>
#include <vector>
#include <string.h>

class Point;

class Board {
public:
	constexpr static int Width = 82; // 80 chars + '\n' + '\0'
	constexpr static int Height = 25;
private:
	char initialBoard[Height][Width] = {
		"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW\n",
	   "W  &                                                                           W\n",
	   "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW\n",
	   "W@@                       $$            W               W                 W    W\n",
	   "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW    W               W                 W    W\n",
	   "W                          $       W    W                WWWW         WWWWW    W\n",
	   "WWWWWWWWWWWWWWWWWWWWWWWW  WW       W    W                   W             W    W\n",
	   "W                         W        W    WWWWWWWWWWWWWWWWWWWWW             W    W\n",
	   "W     WWWWWWWWW           WWWW     W                           $$$        W    W\n",
	   "W             W            W     WWWWWWWWWWWWWWWWWWWWWWWWWWWWW  WWWWWWWWWWW    W\n",
	   "W    WWWWW  WWW            W      LIRAZ'S AND EYAL'S      W               W    W\n",
	   "W    W        WWWWW        W      THUNDERBIRDS PROJECT    W               W    W\n",
	   "W    W            W         WWWWWWWWWWWWWWWWWWWW          W                    W\n",
	   "W    WWWWWWWWWW   W                           WWWWWWWWWWWWWWW    WWW           W\n",
	   "W    W            W          -------------          W           W $ W          W\n",
	   "W    W  WWWWWWWWWWW    W     W            W   W     W           WWWWW     $$$WWW\n",
	   "W    W       W         W     W            W   W     W                     $    W\n",
	   "W            W         W     W            W   W     W                    $$    W\n",
	   "W            W         W     W            W   W      WWWWWWWWWWWWWWWWWWWWW     W\n",
	   "W             $$$      W     W            W $$W                                W\n",
	   "W      WWWWWWWWWWWWWWWWWWWW               W  WW                                W\n",
	   "W      W                       $          W   WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW\n",
	   "       W                      $$$         W                              ##    W\n",
	   "       W                     $$$$$        W                              ##    W\n",
	   "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW\n",
	};
	char currentBoard[Height][Width];
public:
	Board() { resetCurrentBoard(); };
	std::vector<Point> getPoints(char _ch, int _size);
	char get(int x, int y) const { return currentBoard[y][x]; }
	void set(int x, int y, char c) { currentBoard[y][x] = c; }
	void print() const;
	void resetCurrentBoard();
};