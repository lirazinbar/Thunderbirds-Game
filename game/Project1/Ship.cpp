#include "Ship.h"
#include "Point.h"
#include "Board.h"

Ship::Ship(char _ch, int _size, Board* _pBoard) : ch(_ch), size(_size), pBoard(_pBoard) {
	points = _pBoard->getPoints(_ch, _size);
}

void Ship::move(int& difx, int& dify) {
	for (int i = 0; i < size; i++) {
		char newPoint = pBoard->get((points[i].getX() + difx), (points[i].getY() + dify));
		if (newPoint != char(BoardSymbols::BLANK) && newPoint != ch) { // pos is already taken
			difx = dify = 0;
			// If at least one of the points of the ship has reachd the end point
			if (newPoint == char(BoardSymbols::END_POINT)) {
				hasReachedEndPoint = true;
			}
		}
	}
	deleteFromScreen();
	if (hasReachedEndPoint == false) {
		for (int i = 0; i < points.size(); i++) {
			points[i].move(difx, dify);
		}
		drawOnScreen();
	}
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