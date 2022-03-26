#include "Block.h"
#include "Ship.h"
#include "Point.h"
#include "Board.h"

Block::Block(char _ch, int _size, Board* _pBoard) : ch(_ch), size(_size), pBoard(_pBoard) {
	points = _pBoard->getPoints(_ch, _size);
}

void Block::move(int dirx, int diry) {
	deleteFromScreen();
	for (int i = 0; i < points.size(); i++) {
		points[i].move(dirx, diry);
	}
	drawOnScreen();
}

void Block::drawOnScreen() const {
	for (int i = 0; i < points.size(); i++) {
		points[i].drawOnScreen();
	}
}

void Block::deleteFromScreen() const {
	for (int i = 0; i < points.size(); i++) {
		points[i].deleteFromScreen();
	}
}

bool Block::isBlockIncludesPoint(Point p) {
	for (int i = 0; i < points.size(); i++) {
		if (points[i].getX() == p.getX() && points[i].getY() == p.getY())
			return true;
	}
	return false;
}