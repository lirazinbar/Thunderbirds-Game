#pragma once

#include <iostream>
#include <vector>
#include "Utils.h"

class Point;
class Board;

class Block
{
	char ch;
	int size;
	Board* pBoard = nullptr;
	int dirx = 0;
	int diry = 1;
	std::vector<Point> points;
public:
	Block(char _ch, int _size, Board* _pBoard);
	void move();
	void drawOnScreen() const;
	void deleteFromScreen() const;
};

