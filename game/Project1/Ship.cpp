#include "Ship.h"
#include "Point.h"
#include "Board.h"


Ship::Ship(char _ch, int _size, Board* _pBoard) : ch(_ch), size(_size), pBoard(_pBoard) {
	pTopLeft = new Point(ch, _pBoard);
	int y = pTopLeft->getY() + _size / 2 - 1;
	pBottumRight = new Point(pTopLeft->getX() + 1, y, _ch, _pBoard);
}

void Ship::move(int& difx, int& dify) {
	pTopLeft->move(difx, dify);
	pBottumRight->move(difx, dify);
}

void Ship::drawOnScreen() const {
	pTopLeft->drawOnScreen();
	pBottumRight->drawOnScreen();
}
void Ship::deleteFromScreen() const {
	pTopLeft->deleteFromScreen();
	pBottumRight->deleteFromScreen();
}