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
	Point();
	Point(char ch, Board* _pBoard);
	Point(int x1, int y1, char c, Board* _pBoard) : x(x1), y(y1), ch(c), pBoard(_pBoard) {}
	bool operator!() const {
		return x == -1 && y == -1;
	}
	friend std::ostream& operator<<(std::ostream& out, const Point& p) {
		return out << '{' << p.x << ", " << p.y << '}';
	}
	void drawOnScreen() const {
		gotoxy(x, y);
		std::cout << ch;
	}
	void deleteFromScreen() const {
		gotoxy(x, y);
		std::cout << ' ';
	}
	void move(int& difx, int& dify);
	int getX() {
		return x;
	}
	int getY() {
		return y;
	}
};

