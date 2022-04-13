#pragma once

#include <iostream>
#include <vector>
#include "Utils.h"
#include "Board.h"

class Point;
class Board;

class Block {
	char ch;
	int size;
	Board* pBoard = nullptr;
	std::vector<Point> points;
public:
	// Ctor
	Block(char _ch, int _size, Board* _pBoard);
	// Return the points of the block
	std::vector<Point> getPoints() { return points; }
	// Return the size of the block
	int getSize() { return size; }
	// Return the char of the block
	char getChar() { return ch; }
	// Move the block on board according to dirx, diry
	void move(int dirx, int diry);
	// Draw the block on screen
	void drawOnScreen() const;
	// Delete the block from screen
	void deleteFromScreen() const;
	// Checks if the block has the Point p
	bool isBlockIncludesPoint(Point p);
	// Moving the pointsof the block without deleting or drawing
	void setPointsIndexes(int dirx, int diry);
};