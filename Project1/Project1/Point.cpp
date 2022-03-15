#include "Point.h"
#include "Board.h"

void Point::move(int& difx, int& dify) {
	x += difx;
	y += dify;
}

void Point::drawOnScreen() const {
	gotoxy(x, y);
	std::cout << ch;
	pBoard->set(x, y, ch); // draw also in board!
}

void Point::deleteFromScreen() const {
	gotoxy(x, y);
	std::cout << ' ';
	pBoard->set(x, y, ' '); // del also from board
}