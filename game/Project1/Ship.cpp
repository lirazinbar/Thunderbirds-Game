#include "Ship.h"
#include "Point.h"
#include "Board.h"

Ship::Ship(char _ch, int _size, Board* _pBoard) : ch(_ch), size(_size), pBoard(_pBoard) {
	points = _pBoard->getPoints(_ch, _size);
}

void Ship::move(int& difx, int& dify) {
	for (int i = 0; i < size; i++) {
		int new_x = points[i].getX() + difx;
		int new_y = points[i].getY() + dify;
		if (pBoard->get(new_x, new_y) != ' ' && pBoard->get(new_x, new_y) != ch) { // pos is already taken
			difx = dify = 0;
			return;
		}
	}
	deleteFromScreen();
	for (int i = 0; i < points.size(); i++) {
		points[i].move(difx, dify);
	}
	drawOnScreen();
}

void Ship::drawOnScreen() const {
	for (int i = 0; i < points.size(); i++) {
		points[i].drawOnScreen();
	}
}
void Ship::deleteFromScreen() const {
	for (int i = 0; i < points.size(); i++) {
		points[i].deleteFromScreen();
	}
}