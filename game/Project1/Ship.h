#pragma once

#include <iostream>
#include "Utils.h"

class Point;
class Board;

class Ship
{
	char ch;
	int size;
	//int dirX;
	//int dirY;
	Board* pBoard = nullptr;
	Point* pTopLeft = nullptr;
	Point* pBottumRight = nullptr;
public:
	Ship(char _ch, int _size, Board* _pBoard);
	void move(int& difx, int& dify);
	void drawOnScreen() const;
	void deleteFromScreen() const;
	/*bool operator!() const {
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
	*/
};

