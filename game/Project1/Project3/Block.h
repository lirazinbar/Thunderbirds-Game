#pragma once

#include <iostream>
#include <vector>
#include "Utils.h"
#include "Board.h"

class Point;
class Board;

class Block
{
	char ch;
	int size;
	Board* pBoard = nullptr;
	/*int dirx = 0;std::vector<Point>
	int diry = 1;*/
	std::vector<Point> points;
public:
	Block(char _ch, int _size, Board* _pBoard);
	void resetLocatin() { points = pBoard->getPoints(ch, size); }
	std::vector<Point> getPoints() { return points; }
	int getSize() { return size; }
	char getChar() { return ch; }
	void move(int dirx, int diry);
	void drawOnScreen() const;
	void deleteFromScreen() const;
	bool isBlockIncludesPoint(Point p);
};