#pragma once

#include <iostream>
#include "utils.h"

class Board;

class Point {
	int x = -1;
	int y = -1;
	char ch = char(BoardSymbols::BLANK);
	Board* pBoard = nullptr;

	void assign(int _x, int _y, char _ch, Board* _pBoard) {
		x = _x;
		y = _y;
		ch = _ch;
		pBoard = _pBoard;
	}
public:
	Point() {};
	Point(int x1, int y1) : x(x1), y(y1) {};
	Point(int x1, int y1, char c, Board* _pBoard) : x(x1), y(y1), ch(c), pBoard(_pBoard) {}
	Point& operator=(const Point& other) {
		if (&other != this) {
			assign(other.getX(), other.getY(), other.getCh(), other.getPBoard());
		}
		return *this;
	}
	bool operator!() const {
		return x == -1 && y == -1;
	}
	friend std::ostream& operator<<(std::ostream& out, const Point& p) {
		return out << '{' << p.x << ", " << p.y << '}';
	}
	void drawOnScreen() const;
	void deleteFromScreen() const;
	void move(int& difx, int& dify);
	int getX() const { return x; }
	int getY() const { return y; }
	char getCh() const { return ch; }
	Board* getPBoard() const { return pBoard; }
	void setX(int _x) { x = _x; }
	void setY(int _y) { y = _y; }
};

