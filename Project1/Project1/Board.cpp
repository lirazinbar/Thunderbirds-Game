#include "Board.h"
#include "Point.h"
#include "Ship.h"
#include "Color.h"

Board::Board() {
	resetCurrentBoard();
	legend.legendLocation = findCharOnBoard(char(BoardSymbols::LEGEND));
}

std::vector<Point> Board::getPoints(char _ch, int _size) {
	std::vector<Point> points;
	for (int row = 0; row < Height && points.size() < _size; ++row) {
		char curr;
		for (int col = 0; (curr = get(col, row)) != '\n' && points.size() < _size; ++col) {
			if (curr == _ch) {
				Point p = Point(col, row, _ch, this);
				points.push_back(p);
			}
		}
	}
	return points;
}

void Board::print(int activeShip, int timeLeft, int livesCount) const {
	for (size_t row = 0; row < Height; ++row) {
		std::cout << currentBoard[row];
	}
	legend.print(activeShip, timeLeft, livesCount);
}

void Board::resetCurrentBoard() {
	for (size_t row = 0; row < Height; ++row) {
		strcpy_s(currentBoard[row], initialBoard[row]);
	}
}

Point Board::findCharOnBoard(char ch) {
	bool found = false;
	size_t row, col;
	Point res;

	for (row = 0; row < Height && !found; ++row) {
		for (col = 0; col < Width && !found; col++) {
			if (get(col, row) == ch) {
				res = Point(col, row, ch, this);
				found = true;
			}
		}
	}
	return res;
}

std::vector<Point> Board::checkMoving(std::vector<Point> points, int size, char ch, int dirx, int diry) {
	std::vector<Point> collisionPoints;
	for (int i = 0; i < size; i++) {
		int new_x = points[i].getX() + dirx;
		int new_y = points[i].getY() + diry;
		Point newPoint(new_x, new_y, currentBoard[new_y][new_x], this);
		if (currentBoard[new_y][new_x] != ' ' && currentBoard[new_y][new_x] != ch) { // pos is already taken
			collisionPoints.push_back(newPoint);
		}
	}
	return collisionPoints;
}

void Board::Legend::print(int activeShip, int timeLeft, int livesCount) const {
	gotoxy(legendLocation.getX(), legendLocation.getY());
	Color::setTextColor(TextColor::GREEN);
	std::cout << "Active Ship: ";
	printActiveShip(activeShip);
	Color::setTextColor(TextColor::YELLOW);
	std::cout << "       Time Left: ";
	printTimer(timeLeft);
	Color::setTextColor(TextColor::LIGHTRED);
	std::cout << "       Lives: ";
	printLives(livesCount);
	Color::setTextColor(TextColor::WHITE);
}

void Board::Legend::printActiveShip(int activeShip) const {
	Color::setTextColor(TextColor::GREEN);
	gotoxy(legendLocation.getX() + int(PrintPoints::ACTIVE_SHIP_X), legendLocation.getY());
	if (activeShip == int(ShipsIndex::BIG_SHIP)) {
		std::cout << "Big  ";
	}
	else {
		std::cout << "Small";
	}
	Color::setTextColor(TextColor::WHITE);
}

void Board::Legend::printLives(int livesCount) const {
	gotoxy(legendLocation.getX() + int(PrintPoints::LIVES_X), legendLocation.getY());
	std::cout << livesCount;
}

void Board::Legend::printTimer(int timeLeft) const {
	Color::setTextColor(TextColor::YELLOW);
	// x coordination of the timer
	int x = getLegendLocation().getX() + int(PrintPoints::TIMER_X);
	// y coordination of the timer
	int y = getLegendLocation().getY();
	gotoxy(x, y);
	std::cout << timeLeft;
	if (timeLeft == 99) {
		gotoxy(x + 2, y);
		std::cout << char(BoardSymbols::BLANK);  // Erase last digit
	}
	else if (timeLeft == 9) {
		gotoxy(x + 1, y);
		std::cout << char(BoardSymbols::BLANK);  // Erase last digit
	}
	Color::setTextColor(TextColor::WHITE);
}