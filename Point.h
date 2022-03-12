#pragma once

#include <iostream>
#include "utils.h"

class Board;

class Point {
	int x = -1;
	int y = -1;
	char ch;
	Board* pBoard = nullptr;
public:
	Point(char _ch, Board* _pBoard);
	bool operator!() const {
		return x == -1 && y == -1;
	}
	friend std::ostream& operator<<(std::ostream& out, const Point& p) {
		return out << '{' << p.x << ", " << p.y << '}';
	}
	void draw() const {
		gotoxy(x, y);
		std::cout << ch;
	}
	void del() const {
		gotoxy(x, y);
		std::cout << ' ';
	}
	void move(int& difx, int& dify);
};

