#pragma once

#include <iostream>
#include "utils.h"
#include <vector>

class Board;

class Point {
	int x = -1;
	int y = -1;
	char ch = char(BoardSymbols::BLANK);
	Board* pBoard = nullptr;
public:
	//Empty ctor
	Point() {};
	// Ctor with x, y params
	Point(int x1, int y1) : x(x1), y(y1) {};
	// Ctor with x, y, char nd pointer to board params
	Point(int x1, int y1, char c, Board* _pBoard) : x(x1), y(y1), ch(c), pBoard(_pBoard) {}
	// = operator
	Point& operator=(const Point& other) = default;
	// ! operator
	bool operator!() const { return x == -1 && y == -1; }
	// << operator
	friend std::ostream& operator<<(std::ostream& out, const Point& p) {
		return out << '{' << p.x << ", " << p.y << '}';
	}
	// Return the x data member
	int getX() const { return x; }
	// Return the y data member
	int getY() const { return y; }
	// Return the ch data member
	char getCh() const { return ch; }
	// Return the pointr to board
	Board* getPBoard() const { return pBoard; }
	// Change the x data member
	void setX(int _x) { x = _x; }
	// Change the y data member
	void setY(int _y) { y = _y; }
	// Move point according to dirx, diry
	void move(int& difx, int& dify);
	// Draw the char of the point on screen
	void drawOnScreen() const;
	// Delete the point from screen
	void deleteFromScreen() const;
	// Check if points include the point
	bool arePointsIncludePoint(const std::vector<Point>& points) const;
};