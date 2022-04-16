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
	Block(char _ch, int _size, Board* _pBoard, std::vector<Point> _points) : ch(_ch), size(_size), pBoard(_pBoard), points(_points) {}
	// Return the points of the block
	std::vector<Point> getPoints() const { return points; }
	// Return the size of the block
	int getSize() const { return size; }
	// Return the char of the block
	char getChar() const { return ch; }
	// Move the block on board according to dirx, diry
	void move(int dirx, int diry);
	// Draw the block on screen
	void drawOnScreen() const;
	// Delete the block from screen
	void deleteFromScreen() const;
	// Checks if the block has the Point p
	bool isBlockIncludesPoint(Point p) const;
	// Moving the pointsof the block without deleting or drawing
	void setPointsIndexes(int dirx, int diry);
};