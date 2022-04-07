#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Point.h"
#include "Block.h"

class Block;

class Board {
public:
	constexpr static int Width = 82; // 80 chars + '\n' + '\0'
	constexpr static int Height = 25;
private:
	class Legend {
		Point legendLocation;
	public:
		// Return the data member "legendLocation"
		const Point& getLegendLocation() const { return legendLocation; }
		// Print the legend to screen
		void print(int activeShip, int timeLeft, int livesCount) const;
		// Print the active ship to screen
		void printActiveShip(int activeShip) const;
		// Print the current lives count to screen
		void printLives(int livesCount) const;
		// Print the timer to screen
		void printTimer(int timeLeft) const;
		friend class Board;
	};
	Legend legend;
	char initialBoard[Height][Width] = {
	   "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW\n",
	   "W  &                                                                           W\n",
	   "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW\n",
	   "W                    ^^                 W               W                 W    W\n",
	   "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW    W               W                 W    W\n",
	   "W                 W                W    W                WWWW         WWWWW    W\n",
	   "W                WW       WW       W    W                   W             W    W\n",
	   "W                         W        W    WWWWWWWWWWWWWWWWWWWW   +          W    W\n",
	   "W                         WWWW     W                          +++         W    W\n",
	   "W    WWWWWW  WWWWWW        W   WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW  WWWWWWWWWWW    W\n",
	   "W    W            W        W                              W               W    W\n",
	   "W    W   WWWWWWWWWW        W                              W               W    W\n",
	   "W    W            W         WWWWWWWWWWWWWWWWWWWWWWWWW     W                    W\n",
	   "W    WWWWWWWWWW   W                                 WWWWWWWWW    WWW           W\n",
	   "W    W            W                            **   W           W   W          W\n",
	   "W    W  WWWWWWWWWWW    W     WWWWWW WWWWWWW    ^^   W           WWWWW        WWW\n",
	   "W    W       W         W     W            W   W     W                          W\n",
	   "W    W       W         W     W            W   W     W                          W\n",
	   "W            W         W     W            W   W      WWWWWWWWWWWWWWWWWWWWW     W\n",
	   "W            W         W     W            W   W  @@                            W\n",
	   "W      WWWWWWWWWWWWWWWWWWWWWWW            W  WWW                               W\n",
	   "W      W                                  W  WW    ^!!                         W\n",
	   "W      W                          !!!     W        %%     ##                   W\n",
	   "W  E   W                         !!!!!    W        ***    ##                   W\n",
	   "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW\n",
	};
	char currentBoard[Height][Width];
public:
	// Empty ctor
	Board();
	// Getting the legend object
	Legend getLegend() const { return legend; };
	// Getting _size points on board with the char _ch. Return the points in vector
	std::vector<Point> getPoints(char _ch, int _size);
	// Get the char on the board of an x,y point 
	char get(int x, int y) const { return currentBoard[y][x]; }
	// Get the char on the boardof a point object 
	char get(const Point& point) const { return currentBoard[point.getY()][point.getX()]; }
	// Set a point on board which is at x,y location with the char c
	void set(int x, int y, char c) { currentBoard[y][x] = c; }
	// Print board
	void print(int activeShip, int timeLeft, int livesCount) const;
	// Reset current board to the initial start point
	void resetCurrentBoard();
	// Rturning the first Point object on board with the char ch
	Point findCharOnBoard(char ch);
	// From the points the function takes as parameter, the function return only the points that
	// don't collide with something that is not empty space or the ch itself,
	// after moving them dirx, diry
	std::vector<Point> checkMoving(std::vector<Point> points, int size, char ch, int dirx, int diry);
	std::vector<Block> loadBlocksRec();
	std::vector<Point> loadBlockWithChar(char ch, int col, int row, std::vector<Block> blocks, std::vector<Point>& checkedPoints);
	bool blocksIncludePoint(std::vector<Block> blocks, Point p);
	bool arePointsIncludePoint(std::vector<Point> points, int x, int y) const;
	bool isCharOfBlock(char ch);
};