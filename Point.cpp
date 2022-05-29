#include "Point.h"
#include "Board.h"
#include "Game.h"

void Point::move(int& difx, int& dify) {
	x += difx;
	y += dify;
}

void Point::drawOnScreen() const {
	if (Game::getSecondaryGameMode() != GameMode::SILENT) {
		gotoxy(x, y);
		std::cout << ch;
	}
	pBoard->set(x, y, ch); // draw also in board!
}

void Point::deleteFromScreen() const {
	gotoxy(x, y);
	std::cout << char(BoardSymbols::BLANK);
	pBoard->set(x, y, char(BoardSymbols::BLANK)); // del also from board
}

bool Point::arePointsIncludePoint(const std::vector<Point>& points) const {
	int i;

	for (i = 0; i < points.size(); i++) {
		if (points[i].getX() == x && points[i].getY() == y) return true;
	}

	return false;
}