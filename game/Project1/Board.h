#pragma once
#include <iostream>
#include <vector>
#include <string.h>
#include "Point.h"

class Board {
public:
	constexpr static int Width = 82; // 80 chars + '\n' + '\0'
	constexpr static int Height = 25;
private:
	// The X locations of the legend values
	enum class LegendElementsXLocation { ACTIVE_SHIP = 13, TIMER = 36, LIVES = 53 }; 

	class Legend {
		Point legendLocation;
	public:
		const Point& getLegendLocation() const { return legendLocation; }
		void print(int activeShip, int timeLeft, int livesCount) const;
		void printActiveShip(int activeShip) const;
		void printLives(int livesCount) const;
		void printTimer(int timeLeft) const;
		friend class Board;
	};
	Legend legend;
	char initialBoard[Height][Width] = {
		"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW\n",
	   "W  &                                                                           W\n",
	   "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW\n",
	   "W                                       W               W                 W    W\n",
	   "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW    W               W                 W    W\n",
	   "W                                  W    W                WWWW         WWWWW    W\n",
	   "WWWWWWWWWWWWWWWWWWWWWWWW  WW       W    W                   W             W    W\n",
	   "W                         W        W    WWWWWWWWWWWWWWWWWWWWW             W    W\n",
	   "W                         WWWW     W                                  @@  W    W\n",
	   "W    WWWWWWWWWWW  W        W     WWWWWWWWWWWWWWWWWWWWWWWWWWWWW  WWWWWWWWWWW    W\n",
	   "W    W            W$$      W      LIRAZ'S AND EYAL'S      W               W    W\n",
	   "W    W   WWWWWWWWWW$$      W      THUNDERBIRDS PROJECT    W               W    W\n",
	   "W    W            W##       WWWWWWWWWWWWWWWWWWWWWWWWW     W                    W\n",
	   "W    WWWWWWWWWW   W##                               WWWWWWWWW    WWW           W\n",
	   "W    W            W    %%                                       W   W          W\n",
	   "W    W  WWWWWWWWWWW    W     WWWWWWWWWWWWWW   W                 WWWWW         WW\n",
	   "W    W       W         W     W            W   W     W                          W\n",
	   "W    W       W         W     W            W   W     W                          W\n",
	   "W            W         W     W            W   W      WWWWWWWWWWWWWWWWWWWWW     W\n",
	   "W                      W     W            W   W                                W\n",
	   "W      WWWWWWWWWWWWWWWWWWWW               W  WW                                W\n",
	   "W      W                                  W   WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW\n",
	   "W      W                                  W                                    W\n",
	   "W  E   W                                  W                                    W\n",
	   "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW\n",
	};
	char currentBoard[Height][Width];
public:
	Board();
	Legend getLegend() { return legend; }
	std::vector<Point> getPoints(char _ch, int _size);
	char get(int x, int y) const { return currentBoard[y][x]; }
	char get(const Point& point) const { return currentBoard[point.getY()][point.getX()]; }
	void set(int x, int y, char c) { currentBoard[y][x] = c; }
	void print(int activeShip, int timeLeft, int livesCount) const;
	void resetCurrentBoard();
	Point findCharOnBoard(char ch);
	std::vector<Point> checkMoving(std::vector<Point> points, int size, char ch, int dirx, int diry);
};