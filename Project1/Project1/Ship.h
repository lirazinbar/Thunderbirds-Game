#pragma once

#include <iostream>
#include <vector>
#include "Utils.h"

class Point;
class Board;

class Ship
{
	char ch;
	int size;
	Board* pBoard = nullptr;
	std::vector<Point> points;

public:
	Ship(char _ch, int _size, Board* _pBoard);
	void move(int& difx, int& dify);
	void drawOnScreen() const;
	void deleteFromScreen() const;
};

