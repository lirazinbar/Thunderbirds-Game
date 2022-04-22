#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Point.h"
#include "Block.h"
#include "GameScreen.h"
#include "HorizontalGhost.h"

class Block;

class Board {
public:
	constexpr static int Width = 82; // 81 chars + '\0'
	constexpr static int Height = 25;
private:
	class Legend {
		Point legendLocation;
	public:
		// Setting the legend location according the the & char on board
		void setLegendLocation(const Point& _legendLocation) { legendLocation = _legendLocation; }
		// Return the data member "legendLocation"
		const Point& getLegendLocation() const { return legendLocation; }
		// Print the legend to screen
		void print(int activeShip, int timeLeft, int livesCount, int currentScreenNumber) const;
		// Print the active ship to screen
		void printActiveShip(int activeShip) const;
		// Print the current lives count to screen
		void printLives(int livesCount) const;
		// Print the timer to screen
		void printTimer(int timeLeft) const;
		// Print the number of the current game screen
		void printCurrentScreen(int currentScreenNumber) const;
		friend class Board;
	};
	Legend legend;
	char currentBoard[Height][Width] = {0};
public:
	// Empty ctor
	Board() {}
	// Getting the legend object in order to change it
	Legend& getLegend() { return legend; };
	// Get the char on the board of an x,y point 
	char get(int x, int y) const { return currentBoard[y][x]; }
	// Get the char on the boardof a point object 
	char get(const Point& point) const { return currentBoard[point.getY()][point.getX()]; }
	// Set a point on board which is at x,y location with the char c
	void set(int x, int y, char c) { currentBoard[y][x] = c; }
	// params: row number and a line from a text file. Set the relevent row in the board grid 
	void setRow(int row, const char* line) { strcpy_s(currentBoard[row], line); }
	// Getting _size points on board with the char _ch. Return the points in vector
	std::vector<Point> getPoints(char _ch, int _size);
	// Load the blocks on the screen recursively to a vector
	std::vector<Block> loadBlocksRec();
	// Check if there is a block with the char ch
	bool isCharOfBlock(char ch);
	// Load a block on the screen according to a point and a char
	std::vector<Point> loadBlockWithChar(char ch, int col, int row, std::vector<Block> blocks, std::vector<Point>& checkedPoints);
	// Check if the points includes the point with the coordinations x, y
	bool arePointsIncludePoint(const std::vector<Point>& points, int x, int y) const;
	// Check if there is a block in the blocks vector which has the Point p
	bool blocksIncludePoint(const std::vector<Block>& blocks, Point p);
	// Print board
	void print(int activeShip, int timeLeft, int livesCount, int screenNumber) const;
	// Rturning the first Point object on board with the char ch
	Point findCharOnBoard(char ch);
	// From the points the function takes as parameter, the function return only the points that
	// don't collide with something that is not empty space or the ch itself,
	// after moving them dirx, diry
	std::vector<Point> checkMoving(const std::vector<Point>& points, int size, char ch, int dirx, int diry);
	// Searches the hotizontalGhosts from the board and save them
	std::vector<HorizontalGhost> loadHorizontalGhosts();
};