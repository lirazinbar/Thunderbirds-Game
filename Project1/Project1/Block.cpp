#include "Block.h"

#include "Ship.h"
#include "Point.h"
#include "Board.h"


Block::Block(char _ch, int _size, Board* _pBoard) : ch(_ch), size(_size), pBoard(_pBoard) {
	points = _pBoard->getPoints(_ch, _size);
}

void Block::move() {
	for (int i = 0; i < size; i++) {
		int new_x = points[i].getX() + dirx;
		int new_y = points[i].getY() + diry;
		if (pBoard->get(new_x, new_y) != ' ' && pBoard->get(new_x, new_y) != ch) { // pos is already taken
			dirx = diry = 0;
			return;
		}
	}

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
